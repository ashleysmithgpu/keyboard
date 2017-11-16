#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>

#include "usb/usbdrv.h"
#include "i2c/TinyWireM.h"

#define PIN_LED PB1
#define DELAY_MS 50000

#define SET_BIT(p,n) ((p) |= (1 << (n)))
#define CLR_BIT(p,n) ((p) &= ~(1 << (n)))

#define REPSIZE_KEYBOARD 8

const PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
	0x05, 0x01,  // USAGE_PAGE (Generic Desktop)
	0x09, 0x06,  // USAGE (Keyboard)
	0xA1, 0x01,  // COLLECTION (Application)
	0x05, 0x07,  //   USAGE_PAGE (Keyboard)(Key Codes)
	0x19, 0xE0,  //   USAGE_MINIMUM (Keyboard LeftControl)(224)
	0x29, 0xE7,  //   USAGE_MAXIMUM (Keyboard Right GUI)(231)
	0x15, 0x00,  //   LOGICAL_MINIMUM (0)
	0x25, 0x01,  //   LOGICAL_MAXIMUM (1)
	0x75, 0x01,  //   REPORT_SIZE (1)
	0x95, 0x08,  //   REPORT_COUNT (8)
	0x81, 0x02,  //   INPUT (Data,Var,Abs) ; Modifier byte
	0x95, 0x01,  //   REPORT_COUNT (1)
	0x75, 0x08,  //   REPORT_SIZE (8)
	0x81, 0x03,  //   INPUT (Cnst,Var,Abs) ; Reserved byte
	0x95, 0x05,  //   REPORT_COUNT (5)
	0x75, 0x01,  //   REPORT_SIZE (1)
	0x05, 0x08,  //   USAGE_PAGE (LEDs)
	0x19, 0x01,  //   USAGE_MINIMUM (Num Lock)
	0x29, 0x05,  //   USAGE_MAXIMUM (Kana)
	0x91, 0x02,  //   OUTPUT (Data,Var,Abs) ; LED report
	0x95, 0x01,  //   REPORT_COUNT (1)
	0x75, 0x03,  //   REPORT_SIZE (3)
	0x91, 0x03,  //   OUTPUT (Cnst,Var,Abs) ; LED report padding
	0x95, 0x06,  //   REPORT_COUNT (6)
	0x75, 0x08,  //   REPORT_SIZE (8)
	0x15, 0x00,  //   LOGICAL_MINIMUM (0)
	0x25, 0x65,  //   LOGICAL_MAXIMUM (101)
	0x05, 0x07,  //   USAGE_PAGE (Keyboard)(Key Codes)
	0x19, 0x00,  //   USAGE_MINIMUM (Reserved (no event indicated))(0)
	0x29, 0x65,  //   USAGE_MAXIMUM (Keyboard Application)(101)
	0x81, 0x00,  //   INPUT (Data,Ary,Abs)
	0xC0 // END_COLLECTION
};

uint8_t report_buffer[8] = {0,0,0,0,0,0,0,0};
uint8_t idle_rate = 500 / 4; // see HID1_11.pdf sect 7.2.4
uint8_t protocol_version = 0; // see HID1_11.pdf sect 7.2.6

// Poll usb while delaying
void delay(long milli) {

	while (milli > 0) {
		milli--;
		usbPoll();
	}
}

void usbReportSend(uint8_t sz) {

	// perform usb background tasks until the report can be sent, then send it
	while (1) {
		usbPoll(); // this needs to be called at least once every 10 ms
		if (usbInterruptIsReady()) {
			usbSetInterrupt((uint8_t*)report_buffer, sz); // send
			break;

			// see http://vusb.wikidot.com/driver-api
		}
	}
}

void sendKeyPress(char keyPress, char modifiers) {

	uint16_t i = 0;
	for(i = 0; i < 8; ++i)
		report_buffer[i] = 0;

	report_buffer[0] = modifiers;
	report_buffer[1] = 0;
	report_buffer[2] = keyPress;
	usbReportSend(REPSIZE_KEYBOARD);
}


#define LED_NUM_LOCK 1
#define LED_CAPS_LOCK 2
#define LED_SCROLL_LOCK 4
#define LED_COMPOSE 8
#define LED_KANA 16

int main(void) {

	// Init LED pin as output
	DDRB |= (1 << PIN_LED);

	//CLR_BIT(PORTB, PIN_LED);

	// i2c setup
	// set all ports on right side to input
	// left all apart from 3 status leds
	//TinyWireM.beginTransmission(LEFT_I2C_ADDR);
	//TinyWireM.write(

	// usb setup
	cli();
	clock_prescale_set(clock_div_1);
	PORTB &= ~(_BV(USB_CFG_DMINUS_BIT) | _BV(USB_CFG_DPLUS_BIT));
	usbDeviceDisconnect();
	_delay_ms(250);
	usbDeviceConnect();
	usbInit();
	sei();
	_delay_ms(250);

	uint16_t i = 0;

	// Blink !
	for (;;) {

		for(i = 1; i < 8; ++i)
			report_buffer[i] = 0;

		usbReportSend(REPSIZE_KEYBOARD);

		if(report_buffer[0] & LED_CAPS_LOCK)
			SET_BIT(PORTB, PIN_LED);
		else
			CLR_BIT(PORTB, PIN_LED);
		//PORTB ^= (1 << PIN_LED);
		/*sendKeyPress(11, 0);
		sendKeyPress(0, 0);
		// PORTB ^= (1 << PIN_LED);
		delay(DELAY_MS);
		sendKeyPress(8, 0);
		sendKeyPress(0, 0);
		// PORTB ^= (1 << PIN_LED);
		delay(DELAY_MS);
		sendKeyPress(15, 0);
		sendKeyPress(0, 0);
		// PORTB ^= (1 << PIN_LED);
		delay(DELAY_MS);
		sendKeyPress(15, 0);
		sendKeyPress(0, 0);
		// PORTB ^= (1 << PIN_LED);
		delay(DELAY_MS);
		sendKeyPress(18, 0);
		sendKeyPress(0, 0);*/
	}

	return 0;
}

usbMsgLen_t usbFunctionSetup(uchar data[8]) {

	// see HID1_11.pdf sect 7.2 and http://vusb.wikidot.com/driver-api
	usbRequest_t *rq = (void *)data;

	if ((rq->bmRequestType & USBRQ_TYPE_MASK) != USBRQ_TYPE_CLASS)
		return 0; // ignore request if it's not a class specific request

	// see HID1_11.pdf sect 7.2
	switch (rq->bRequest) {
		case USBRQ_HID_GET_IDLE:
			usbMsgPtr = &idle_rate;
			return 1; // send 1 byte
		case USBRQ_HID_SET_IDLE:
			idle_rate = rq->wValue.bytes[1]; // read in idle rate
			return 0;
		case USBRQ_HID_GET_PROTOCOL:
			usbMsgPtr = &protocol_version;
			return 1; // send 1 byte
		case USBRQ_HID_SET_PROTOCOL:
			protocol_version = rq->wValue.bytes[1];
			return 0;
		case USBRQ_HID_GET_REPORT:
			usbMsgPtr = (uint8_t*)&report_buffer; // send the report data
			return 8;
		case USBRQ_HID_SET_REPORT:
			if (rq->wLength.word == 1) {
				// 1st is the report byte, data is the 2nd byte.
				// We don't check report type (it can only be output or feature)
				// we never implemented "feature" reports so it can't be feature
				// so assume "output" reports
				// this means set LED status
				// since it's the only one in the descriptor
				return USB_NO_MSG; // send nothing but call usbFunctionWrite
			} else {
				return 0;
			}
		default: // do not understand data, ignore
			return 0;
	}
}

// Called when reading data from usb
uchar usbFunctionWrite(uchar * data, uchar len) {

	report_buffer[0] = data[0];

	return 1;
}

