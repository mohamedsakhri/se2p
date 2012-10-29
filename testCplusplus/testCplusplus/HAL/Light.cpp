/*
 * Light.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#include "Light.h"
#include "HWaccess.h"


Light::Light() {
	// TODO Auto-generated constructor stub

}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::green_Light_on() {
	Light::light_on( BIT_5);
}

void Light::green_Light_off() {
	Light::light_off( BIT_5);
}
void Light::yellow_Light_on() {
	Light::light_on( BIT_6);
}

void Light::yellow_Light_off() {
	Light::light_off( BIT_6);
}

void Light::red_Light_on() {
	Light::light_on( BIT_7);
}

void Light::red_Light_off() {
	Light::light_off( BIT_7);
}

void Light::light_on(uint8_t bitNumber) {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, bitNumber | portAState);
}

void Light::light_off(uint8_t bitNumber) {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, bitNumber ^ portAState);
}
