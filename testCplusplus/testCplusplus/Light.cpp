/*
 * Light.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#include "Light.h"

Light::Light() {
	// TODO Auto-generated constructor stub

}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

void Light::greenLightOn() {
	Light::lightOn( BIT_5);
}

void Light::greenLightOff() {
	Light::lightOn( BIT_5);
}
void Light::yellowLightOn() {
	Light::lightOn( BIT_6);
}

void Light::yellowLightOff() {
	Light::lightOn( BIT_6);
}

void Light::redLightOn() {
	Light::lightOn( BIT_7);
}

void Light::redLightOff() {
	Light::lightOn( BIT_7);
}

void Light::lightOn(uint8_t bitNumber) {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, bitNumber | portAState);
}

void Light::lightOff(uint8_t bitNumber) {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, bitNumber ^ portAState);
}
