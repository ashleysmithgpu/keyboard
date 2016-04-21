
#include <inttypes.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/pgmspace.h>

#include "usb_keyboard.h"
#include "usb_key_ids.h"

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

#define LED_0 0
#define LED_1 1
#define LED_2 2
#define NUM_LEDS 3

uint8_t previous_led_values[NUM_LEDS] = {0, 0, 0};

const uint8_t row_pin_numbers[] = {0,1,2,3,7};
const uint8_t column_pin_numbers[] = {0,1,4,5,6,7};

#define NUM_FUNCTION_KEYS 3
#define NUM_MAIN_KEYS_ROWS 5
#define NUM_MAIN_KEYS_COLS 6
#define NUM_PHYSICAL_KEYS (NUM_MAIN_KEYS_ROWS * NUM_MAIN_KEYS_COLS)
#define NUM_TOTAL_KEYS (NUM_FUNCTION_KEYS + NUM_PHYSICAL_KEYS)
#define MAX_NUM_DELTAS 6

#define KEY_PRESSED 1
#define KEY_RELEASED 0

#define NUM_FRAMES_TO_KEEP 2

#define NUM_MODIFIER_KEYS_LEFT 5
const uint8_t modifier_keys_indices_left[] = {1, 2, 21, 27, 28};

uint16_t physical_key_to_hid_key_id_map_left [] = {
	KEY_RESERVED, KEY_LEFT_GUI, KEY_RIGHT_ALT,
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_MINUS,
	KEY_LEFT_BRACE, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T,
	KEY_HASH, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G,
	KEY_LEFT_SHIFT, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B,
	KEY_LEFT_CTRL, KEY_LEFT_ALT, KEY_RESERVED, KEY_TILDE, KEY_BACKSPACE, KEY_ENTER
};

#define NUM_MODIFIER_KEYS_RIGHT 1
const uint8_t modifier_keys_indices_right[] = {26};

uint16_t physical_key_to_hid_key_id_map_right [] = {
	KEY_MENU, KEY_INSERT, KEY_PRINTSCREEN,
	KEY_EQUAL, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
	KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_RIGHT_BRACE,
	KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE,
	KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_RIGHT_SHIFT,
	KEY_SPACE, KEY_DELTE, KEY_TAB, KEY_CAPS_LOCK, KEY_BACKSLASH, KEY_ESC
};

inline void reset_keys_status(uint8_t * status) {

	for(uint8_t i = 0; i < NUM_TOTAL_KEYS; ++i) {

		status[i] = 0;
	}
}

inline void get_keys_status_from_hw(uint8_t * status) {

	for(uint8_t row = 0; row < NUM_MAIN_KEYS_ROWS; ++row) {

		// Set row pin to input mode and set to invert input
		PORTB |= 1 << row_pin_numbers[row];

		for(uint8_t col = 0; col < NUM_MAIN_KEYS_COLS; ++col) {

			// Set column pin to output mode and output zero
			DDRF |= 1 << column_pin_numbers[col];

			uint8_t button_number = NUM_FUNCTION_KEYS + row * NUM_MAIN_KEYS_COLS + col;

			// Measure, zero means key pressed
			status[button_number] = !(PINB & (1 << row_pin_numbers[row])) ? KEY_PRESSED : KEY_RELEASED;

			DDRF &= ~(1 << column_pin_numbers[col]);
		}

		PORTB &= ~(1 << row_pin_numbers[row]);
	}

	// Pull up the 3 function button pins and check if they are pulled down
	PORTB |= (1<<4);
	PORTC |= (1<<7);
	PORTD |= (1<<6);
	if(!(PINB & (1<<4)))
		status[2] = true;//button 3
	if(!(PIND & (1<<6)))
		status[1] = true;//button 2
	if(!(PINC & (1<<7)))
		status[0] = true;//button 1
	//Now pull back down function buttons
	PORTB &= ~(1<<4);
	PORTC &= ~(1<<7);
	PORTD &= ~(1<<6);
}

inline void get_key_deltas(const uint8_t * current_status, const uint8_t * previous_status, uint8_t * restrict deltas, uint8_t * restrict num_deltas) {

	assert(current_status != deltas);
	assert(previous_status != deltas);
	assert(num_deltas != deltas);

	*num_deltas = 0;

	for(uint8_t i = 0; i < NUM_TOTAL_KEYS; ++i) {

		if(current_status[i] != previous_status[i]) {

			if(*num_deltas < MAX_NUM_DELTAS - 1) {

				deltas[num_deltas] = i;

				num_deltas++;
			} else {

				// TODO: do something?
			}
		}
	}
}


inline void set_modifier_keys_from_physical_keys(const uint8_t * physical_keys_left) {

	uint8_t temp_modifier_keys = 0;

	if(physical_keys_left) {

		for(uint8_t i = 0; i < NUM_MODIFIER_KEYS_LEFT; ++i) {

			temp_modifier_keys |= physical_keys_left[modifier_keys_indices_left[i]];
		}
	}

	// The USB interrupts will read this
	keyboard_modifier_keys = temp_modifier_keys;
}

inline void append_modifier_keys_from_slaves(uint8_t modifier_keys) {

	keyboard_modifier_keys |= modifier_keys;
}

inline void debounce_keys() {

}

inline void set_keys_pressed_from_debounced_keys(const uint8_t * deltas, uint8_t * num_keys_pressed) {

	assert(deltas != 0);
	assert(num_keys_pressed != 0);

	*num_keys_pressed = 0;

	for(uint8_t i = 0; i < MAX_NUM_DELTAS; ++i) {

		keyboard_keys[i] = 0;
	}

	for(uint8_t i = 0; i < NUM_TOTAL_KEYS; ++i) {

		if(!is_left_modifier_key(i)) {

			if(num_keys_pressed < MAX_NUM_DELTAS - 1) {

				keyboard_keys[*num_keys_pressed] = physical_keys[i];

				*num_keys_pressed++;
			} else {

				// ?
			}
		}
	}
}

void set_led_status(uint8_t led_id, uint8_t value) {

	if(led_id < NUM_LEDS) {

		if(previous_led_values[led_id] != value) {

			switch(led_id) {
				case LED_0: {
					if(value == 0) {
						DDRD &= ~(1<<7);
						OCR4D = 0;
					} else {
						DDRD |= 1 << 7;
						OCR4D = value;
					}
				} break;
				case LED_1: {
					if(value == 0) {
						DDRB &= ~(1<<6);
						OCR1B = 0;
					} else {
						DDRB |= 1 << 6;
						OCR1B = value;
					}
				} break;
				case LED_2: {
					if(value == 0) {
						DDRB &= ~(1<<5);
						OCR1A = 0;
					} else {
						DDRB |= 1 << 5;
						OCR1A = value;
					}
				} break;
				default: {
					// ?
				} break;
			}

			previous_led_values[led_id] = value;
		}
	}
}

void update_leds_from_usb_results() {

	// Update the leds with the status from the usb communications
	// TODO: figure out after two halfs working
	if(keyboard_leds & LED_CAPS_LOCK) {
		set_led_status(LED_0, 255);
	}
	if(keyboard_leds & LED_NUM_LOCK) {
		set_led_status(LED_1, 255);
	}
	if(keyboard_leds & LED_SCROLL_LOCK) {
		set_led_status(LED_2, 255);
	}
}

int main() {

	uint8_t physical_key_status[NUM_FRAMES_TO_KEEP][NUM_TOTAL_KEYS];
	uint8_t current_status = 0;
	uint8_t key_deltas[NUM_TOTAL_KEYS];
	uint8_t num_deltas = 0;
	uint8_t num_keys_pressed = 0;

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

	usb_init();

	for(;;) {

		get_keys_status_from_hw(physical_key_status[current_status]);

		get_key_deltas(physical_key_status[current_status], physical_key_status[(current_status - 1) % NUM_FRAMES_TO_KEEP], physical_key_deltas, &num_deltas);

		set_modifier_keys_from_physical_keys(physical_key_status[current_status]);

		// TODO
		append_modifier_keys_from_slaves(0);

		set_keys_pressed_from_physical_keys(physical_key_status, &num_keys_pressed);

		update_leds_from_usb_results();

		current_status = (current_status + 1) % NUM_FRAMES_TO_KEEP;
	}

	return 0;
}

