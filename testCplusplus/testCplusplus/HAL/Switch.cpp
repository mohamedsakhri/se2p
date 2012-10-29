/*
 * Switch.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#include "Switch.h"
#include "HWaccess.h"


Switch::Switch() {
	// TODO Auto-generated constructor stub

}

Switch::~Switch() {
	// TODO Auto-generated destructor stub
}

bool Switch::is_Switch_Open() {
	// TODO : return the right value !
	return (in8(DIGITAL_CARD_CROUP0_PORTA) | BIT_4) ;
}

void Switch::open_Switch() {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, BIT_4 | portAState);
}

void Switch::close_Switch() {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, BIT_2 | portAState);
}


