
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#define static_assert _Static_assert

#include <avr/io.h>
//#include <avr/delay.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "usb_keyboard.h"
#include "usb_key_ids.h"
#include "twi.h"

#define LEFT_KEYBOARD 0
#define RIGHT_KEYBOARD 1

// Define one of these to determine which size we are running on
#define KEYBOARD_SIDE LEFT_KEYBOARD
//#define KEYBOARD_SIDE RIGHT_KEYBOARD

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

#define LED_0 0
#define LED_1 1
#define LED_2 2
#define NUM_LEDS 3

static const uint8_t previous_led_values[NUM_LEDS] = {0, 0, 0};

static const uint8_t row_pin_numbers[] = {0,1,2,3,7};
static const uint8_t column_pin_numbers[] = {0,1,4,5,6,7,8};

#define NUM_FUNCTION_KEYS 3
#define NUM_MAIN_KEYS_ROWS 5
#define NUM_MAIN_KEYS_COLS 7
#define NUM_PHYSICAL_KEYS (NUM_MAIN_KEYS_ROWS * NUM_MAIN_KEYS_COLS)
#define NUM_TOTAL_KEYS (NUM_FUNCTION_KEYS + NUM_PHYSICAL_KEYS)

// TODO: this may be bigger if we change the usb protocol
#define MAX_USB_NUM_KEYS_DOWN 6

#define KEY_PRESSED 1
#define KEY_RELEASED 0

#define KEY_CFN_LEFT 200
#define KEY_CFN_RIGHT 201
#define KEY_INDEX_CUSTOM_FN_LEFT 32
#define KEY_INDEX_CUSTOM_FN_RIGHT 30

#define NUM_FRAMES_TO_KEEP 2

#define NUM_MODIFIER_KEYS_LEFT 4
static const uint8_t modifier_keys_indices_left[] = {21, 28, 29, 30};

static const uint8_t physical_key_to_hid_key_id_map_left [] = {
	KEY_NUM_LOCK,	KEY_ESC,				KEY_1,			KEY_2,			KEY_3,			KEY_4,		KEY_5,
	KEY_TAB,		KEY_LEFT_BRACE,			KEY_Q,			KEY_W,			KEY_E,			KEY_R,		KEY_T,
	KEY_CAPS_LOCK,	KEY_HASH,				KEY_A,			KEY_S,			KEY_D,			KEY_F,		KEY_G,
	KEY_LEFT_SHIFT,	KEY_AMERICAN_BACKSLASH,	KEY_Z,			KEY_X,			KEY_C,			KEY_V,		KEY_B,
	KEY_LEFT_CTRL,	KEY_LEFT_GUI,			KEY_LEFT_ALT,	KEY_RESERVED,	KEY_CFN_LEFT,	KEY_ENTER,	KEY_SPACE/*TODO:dup?*/
};

static const uint8_t physical_key_to_hid_key_id_map_left_fn [] = {
	KEY_NUM_LOCK,	KEY_TILDE,				KEY_F1,			KEY_F2,			KEY_F3,			KEY_F4,		KEY_F5,
	KEY_TAB,		KEY_LEFT_BRACE,			KEY_Q,			KEY_W,			KEY_E,			KEY_R,		KEY_T,
	KEY_CAPS_LOCK,	KEY_HASH,				KEY_HOME,		KEY_PAGE_UP,	KEY_PAGE_DOWN,	KEY_END,	KEY_G,
	KEY_LEFT_SHIFT,	KEY_AMERICAN_BACKSLASH,	KEY_Z,			KEY_X,			KEY_C,			KEY_V,		KEY_B,
	KEY_LEFT_CTRL,	KEY_LEFT_GUI,			KEY_LEFT_ALT,	KEY_RESERVED,	KEY_CFN_LEFT,	KEY_ENTER,	KEY_SPACE/*TODO:dup?*/
};

#define NUM_MODIFIER_KEYS_RIGHT 4
static const uint8_t modifier_keys_indices_right[] = {27, 32, 33, 34};

static const uint8_t physical_key_to_hid_key_id_map_right [] = {
	KEY_6,		KEY_7,			KEY_8,			KEY_9,			KEY_0,			KEY_MINUS,				KEY_EQUAL,
	KEY_Y,		KEY_U,			KEY_I,			KEY_O,			KEY_P,			KEY_RIGHT_BRACE,		KEY_DELETE,
	KEY_H,		KEY_J,			KEY_K,			KEY_L,			KEY_SEMICOLON,	KEY_QUOTE,				KEY_ENTER/*TODO:dup?*/,
	KEY_N,		KEY_M,			KEY_COMMA,		KEY_PERIOD,		KEY_SLASH,		KEY_RESERVED/*TODO*/,	KEY_RIGHT_SHIFT,
	KEY_SPACE,	KEY_BACKSPACE,	KEY_CFN_RIGHT,	KEY_RESERVED,	KEY_RIGHT_ALT,	KEY_RIGHT_GUI,			KEY_RIGHT_CTRL
};

static const uint8_t physical_key_to_hid_key_id_map_right_fn [] = {
	KEY_F6,		KEY_F7,			KEY_F8,			KEY_F9,			KEY_F10,		KEY_F11,				KEY_F12,
	KEY_Y,		KEY_U,			KEY_I,			KEY_O,			KEY_PRINTSCREEN,KEY_RIGHT_BRACE,		KEY_INSERT,
	KEY_LEFT,	KEY_UP,			KEY_DOWN,		KEY_RIGHT,		KEY_SEMICOLON,	KEY_QUOTE,				KEY_ENTER/*TODO:dup?*/,
	KEY_N,		KEY_M,			KEY_COMMA,		KEY_PERIOD,		KEY_SLASH,		KEY_RESERVED/*TODO*/,	KEY_RIGHT_SHIFT,
	KEY_SPACE,	KEY_BACKSPACE,	KEY_CFN_RIGHT,	KEY_RESERVED,	KEY_RIGHT_ALT,	KEY_RIGHT_GUI,			KEY_RIGHT_CTRL
};

static const uint8_t physical_key_to_hid_key_id_map_right_num [] = {
	KEY_F6,		KEYPAD_7,		KEYPAD_8,		KEYPAD_9,		KEYPAD_ASTERIX,	KEY_F11,				KEY_F12,
	KEY_Y,		KEYPAD_4,		KEYPAD_5,		KEYPAD_6,		KEYPAD_SLASH,	KEY_RIGHT_BRACE,		KEY_INSERT,
	KEY_LEFT,	KEYPAD_1,		KEYPAD_2,		KEYPAD_3,		KEYPAD_PLUS,	KEY_QUOTE,				KEY_ENTER/*TODO:dup?*/,
	KEY_N,		KEYPAD_ENTER,	KEYPAD_0,		KEYPAD_PERIOD,	KEYPAD_MINUS,	KEY_RESERVED/*TODO*/,	KEY_RIGHT_SHIFT,
	KEY_SPACE,	KEY_BACKSPACE,	KEY_CFN_RIGHT,	KEY_RESERVED,	KEY_RIGHT_ALT,	KEY_RIGHT_GUI,			KEY_RIGHT_CTRL
};

#if KEYBOARD_SIDE == LEFT_KEYBOARD
#define NUM_MODIFIER_KEYS NUM_MODIFIER_KEYS_LEFT
#define KEY_CFN KEY_CFN_LEFT
#define KEY_INDEX_CUSTOM_FN KEY_INDEX_CUSTOM_FN_LEFT
#define modifier_keys_indices modifier_keys_indices_left
#define physical_key_to_hid_key_id_map physical_key_to_hid_key_id_map_left
#define physical_key_to_hid_key_id_map_fn physical_key_to_hid_key_id_map_left_fn
#else
#define NUM_MODIFIER_KEYS NUM_MODIFIER_KEYS_RIGHT
#define KEY_CFN KEY_CFN_RIGHT
#define KEY_INDEX_CUSTOM_FN KEY_INDEX_CUSTOM_FN_RIGHT
#define modifier_keys_indices modifier_keys_indices_right
#define physical_key_to_hid_key_id_map physical_key_to_hid_key_id_map_right
#define physical_key_to_hid_key_id_map_fn physical_key_to_hid_key_id_map_right_fn
#endif

bool running_as_master = false;
bool running_as_slave = false;
bool have_slave = false;

uint8_t debounce_timers[NUM_TOTAL_KEYS];

#define DEBOUNCE_TIME 100
#define I2C_DATA_NUM_KEYS 14

struct i2c_data_packet {
	uint8_t modifiers;
	bool fn_key;
	uint8_t keys[I2C_DATA_NUM_KEYS];
};

#define I2C_DATA_SIZE 16
static_assert(sizeof(struct i2c_data_packet) == I2C_DATA_SIZE, "i2c_data_packet and I2C_DATA_SIZE size inconsistent");

struct i2c_data_packet outbound_i2c_data;
bool valid_data_ready = false;

void reset_keys_status(uint8_t * status) {

	for(uint8_t i = 0; i < NUM_TOTAL_KEYS; ++i) {

		status[i] = 0;
	}
}

void get_keys_status_from_hw_and_debounce(uint8_t * status, const uint8_t * previous_status) {

	for(uint8_t row = 0; row < NUM_MAIN_KEYS_ROWS; ++row) {

		// Set row pin to input mode and set to invert input
		PORTB |= 1 << row_pin_numbers[row];

		for(uint8_t col = 0; col < NUM_MAIN_KEYS_COLS; ++col) {

			// Set column pin to output mode and output zero
			DDRF |= 1 << column_pin_numbers[col];

			uint8_t button_number = NUM_FUNCTION_KEYS + row * NUM_MAIN_KEYS_COLS + col;

			// If we are not waiting, check button press and start the debounce timer if button changed
			if(debounce_timers[button_number] == 0) {

				// Measure, zero means key pressed
				status[button_number] = !(PINB & (1 << row_pin_numbers[row])) ? KEY_PRESSED : KEY_RELEASED;

				if(status[button_number] != previous_status[button_number]) {

					debounce_timers[button_number] = DEBOUNCE_TIME;
				}
			}

			DDRF &= ~(1 << column_pin_numbers[col]);
		}

		PORTB &= ~(1 << row_pin_numbers[row]);
	}
}

void get_keys_down(const uint8_t * current_status, uint8_t * restrict keys_down, uint8_t * restrict num_keys_down, uint8_t * modifier_keys, bool * fn_key) {

	assert(current_status != keys_down);
	assert(num_keys_down != keys_down);

	*modifier_keys = 0;

	for(uint8_t i = 0; i < NUM_MODIFIER_KEYS; ++i) {
		*modifier_keys |= current_status[modifier_keys_indices[i]];
	}

	*fn_key = current_status[KEY_INDEX_CUSTOM_FN] == KEY_PRESSED;

	*num_keys_down = 0;

	for(uint8_t i = 0; i < NUM_TOTAL_KEYS; ++i) {

		// Ignore modifier keys and fn keys
		for(uint8_t j = 0; j < NUM_MODIFIER_KEYS; ++j)
			if(modifier_keys_indices[i] == i)
				continue;

		if(i == KEY_INDEX_CUSTOM_FN)
			continue;

		if(current_status[i] == KEY_PRESSED && *num_keys_down < NUM_TOTAL_KEYS - 1) {

			keys_down[*num_keys_down] = i;

			num_keys_down++;
		} else {

			// TODO: do something?
		}
	}
}

uint8_t usb_key_id_from_index_side_fn(uint8_t key_id, uint8_t side, bool fn_key, bool num_lock) {

	const uint8_t * layer = 0;
	if(side == LEFT_KEYBOARD) {

		layer = (fn_key ? physical_key_to_hid_key_id_map_left_fn : physical_key_to_hid_key_id_map_left);
	} else {

		layer = (fn_key ? physical_key_to_hid_key_id_map_right_fn : physical_key_to_hid_key_id_map_right);
		if(num_lock)
			layer = physical_key_to_hid_key_id_map_right_num;
	}

	return layer[key_id];
}

void debounce_tick(void) {

	for(uint8_t i = 0; i < NUM_TOTAL_KEYS; ++i) {

		if(debounce_timers[i] > 0)
			debounce_timers[i]--;
	}
}

void update_leds_from_usb_results(void) {

	// Update the leds with the status from the usb communications
	// TODO: figure out after two halfs working
	if(keyboard_leds & LED_CAPS_LOCK) {
		DDRD |= 1 << 7;
		OCR4D = 255;
	} else {
		DDRD &= ~(1<<7);
		OCR4D = 0;
	}
	if(keyboard_leds & LED_NUM_LOCK) {
		DDRB |= 1 << 6;
		OCR1B = 255;
	} else {
		DDRB &= ~(1<<6);
		OCR1B = 0;
	}
	if(keyboard_leds & LED_SCROLL_LOCK) {
		DDRB |= 1 << 5;
		OCR1A = 255;
	} else {
		DDRB &= ~(1<<5);
		OCR1A = 0;
	}
}

void twi_interrupt_slave_tx_event(void) {

	// Called when we are a slave and the master is requesting a write
	if(valid_data_ready) {

		twi_transmit((uint8_t*)&outbound_i2c_data, I2C_DATA_SIZE);
		valid_data_ready = false;
	} else {

		uint8_t zeros[I2C_DATA_SIZE] = {0};
		twi_transmit(zeros, I2C_DATA_SIZE);
	}
}

void twi_interrupt_slave_rx_event(uint8_t * buffer, int num_bytes) {

	if(num_bytes != I2C_DATA_SIZE)
		return;

	if(buffer[0] == 'S')
		// We are master
		running_as_slave = true;

	//if(buffer[0] == 'L')
		// Set led statuses
}

int main(void) {

	uint8_t physical_key_status[NUM_FRAMES_TO_KEEP][NUM_TOTAL_KEYS];
	uint8_t current_status = 0;
	uint8_t previous_status = 0;
	uint8_t physical_keys_down[NUM_TOTAL_KEYS];
	uint8_t num_keys_down = 0;

	CPU_PRESCALE(0);

	_delay_ms(5);

	DDRF = 0;
	PORTF = 0;

	DDRB = 0;
	PORTB = 0;

	// Turn on I2C internal pullups. Not really necessary, since we have external pullups too
	PORTD |= (1<<0) | (1<<1);

	for(uint8_t i = 0; i < NUM_FRAMES_TO_KEEP; ++i)
		reset_keys_status(physical_key_status[i]);

	reset_keys_status(debounce_timers);

	// Init usb
	usb_init();

	// Init i2c
	twi_setAddress(1);
	twi_attachSlaveTxEvent(twi_interrupt_slave_tx_event);
	twi_attachSlaveRxEvent(twi_interrupt_slave_rx_event);
	twi_init();

	// Check if we are the master (connected by usb) or the slave (connected by i2c)
	while(!running_as_master && !running_as_slave) {

		running_as_master = usb_configured() > 0;
	}

	if(running_as_master) {

		running_as_slave = false;

		// Set i2c as master
		twi_setAddress(0);

		// Write slave init data
		uint8_t data[I2C_DATA_SIZE] = {'S'};
		uint8_t result = twi_writeTo(1, data, I2C_DATA_SIZE, true, true);
		have_slave = result == 0;
	}

	if(running_as_slave) {

		running_as_master = false;

		// Turn off usb
		UDCON = 1 << DETACH;
		USBCON = 1 << FRZCLK;
		PLLCSR &= ~(1 << PLLE);
		UHWCON &= ~(1 << UVREGE);
	}

	uint8_t num_slave_keys_pressed = 0;
	uint8_t slave_keys_pressed[I2C_DATA_SIZE];
	uint8_t modifier_keys = 0;
	uint8_t slave_modifier_keys = 0;
	bool any_fn_key_pressed = false;

	for(;;) {

		debounce_tick();

		get_keys_status_from_hw_and_debounce(physical_key_status[current_status], physical_key_status[previous_status]);

		get_keys_down(physical_key_status[current_status], physical_keys_down, &num_keys_down, &modifier_keys, &any_fn_key_pressed);

		if(running_as_slave) {

			outbound_i2c_data.fn_key = any_fn_key_pressed;
			outbound_i2c_data.modifiers = modifier_keys;
			for(uint8_t i = 0; i < I2C_DATA_NUM_KEYS; ++i)
				outbound_i2c_data.keys[i] = 0;

			// TODO: discard for now
			if(num_keys_down > I2C_DATA_NUM_KEYS)
				num_keys_down = I2C_DATA_NUM_KEYS;
			assert(num_keys_down <= I2C_DATA_NUM_KEYS);

			for(uint8_t i = 0; i < num_keys_down; ++i)
				outbound_i2c_data.keys[i] = physical_keys_down[i] + 1;

			valid_data_ready = true;

		} else {

			struct i2c_data_packet data;
			twi_readFrom(1, (uint8_t*)&data, I2C_DATA_SIZE, true);

			num_slave_keys_pressed = 0;

			slave_modifier_keys = data.modifiers;
			any_fn_key_pressed |= data.fn_key;

			// TODO: make num lock a non toggle key
			bool num_lock_enabled = (keyboard_leds & LED_NUM_LOCK) > 0 ? true : false;

			for(uint8_t i = 0; i < I2C_DATA_NUM_KEYS; ++i) {

				if(data.keys[i] > 0) {

					slave_keys_pressed[i] = data.keys[i] - 1;
					num_slave_keys_pressed++;
				}
			}

			// TODO: remove duplicates from both sides of keyboard

			// TODO: discard for now
			if(num_keys_down > MAX_USB_NUM_KEYS_DOWN)
				num_keys_down = MAX_USB_NUM_KEYS_DOWN;
			assert(num_keys_down <= MAX_USB_NUM_KEYS_DOWN);

			uint8_t i = 0;
			for(i = 0; i < num_keys_down; ++i) {

				// This variable is passed to the usb controller directly
				keyboard_keys[i] = usb_key_id_from_index_side_fn(physical_keys_down[i], 0, any_fn_key_pressed, num_lock_enabled);
			}

			for(i = 0; i < MAX_USB_NUM_KEYS_DOWN; ++i) {

				// This variable is passed to the usb controller directly
				keyboard_keys[i] = usb_key_id_from_index_side_fn(slave_keys_pressed[i], 1, any_fn_key_pressed, num_lock_enabled);
			}

			// This variable is passed to the usb controller directly
			keyboard_modifier_keys = modifier_keys | slave_modifier_keys;
		}

		update_leds_from_usb_results();

		previous_status = current_status;
		current_status = (current_status + 1) % NUM_FRAMES_TO_KEEP;
	}

	return 0;
}

