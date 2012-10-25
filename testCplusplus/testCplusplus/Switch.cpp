/*
 * Switch.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#include "Switch.h"

Switch::Switch() {
	// TODO Auto-generated constructor stub

}

Switch::~Switch() {
	// TODO Auto-generated destructor stub
}

bool Switch::isOpen() {
	return (in8(DIGITAL_CARD_CROUP0_PORTA) | BIT_4) ;
}

void Switch::open() {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, BIT_4 | portAState);
}

void Switch::close() {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, BIT_2 | portAState);
}


