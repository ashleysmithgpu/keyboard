// Taken from http://www.pjrc.com/teensy/usb_keyboard.html

#if !defined(USB_KEYBOARD_H)
#define USB_KEYBOARD_H

#include <stdint.h>

void usb_init(void);
uint8_t usb_configured(void);
void usb_disable(void);

int8_t usb_keyboard_send(void);

extern uint8_t keyboard_modifier_keys;
extern uint8_t keyboard_keys[6];
extern volatile uint8_t keyboard_leds;

#endif

