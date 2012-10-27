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

void LED::Start_LED_on() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_0 | portCState);
}

void LED::Start_LED_off() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_0 ^ portCState);
}

void LED::Reset_LED_on() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_1 | portCState);
}

void LED::Reset_LED_off() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_1 ^ portCState);
}

void LED::Q1_LED_on() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_2 | portCState);
}

void LED::Q1_LED_off() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_2 ^ portCState);
}
void LED::Q2_LED_on() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_3 | portCState);
}

void LED::Q2_LED_on() {
	uint8_t portCState = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, BIT_3 ^ portCState);
}
