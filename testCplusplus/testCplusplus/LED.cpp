/*
 * LED.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#include "LED.h"

LED::LED() {
	// TODO Auto-generated constructor stub

}

LED::~LED() {
	// TODO Auto-generated destructor stub
}

void LED::flashStartLED() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_0 | portCState);
}

void LED::darkStartLED() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_0 ^ portCState);
}

void LED::flashResetLED() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_1 | portCState);
}

void LED::darkResetLED() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_1 ^ portCState);
}

void LED::flashQ1LED() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_2 | portCState);
}

void LED::darkQ1LED() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_2 ^ portCState);
}
void LED::flashQ2LED() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_3 | portCState);
}

void LED::darkQ2LED() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_3 ^ portCState);
}
