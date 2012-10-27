/*
 * Motor.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: simohamed
 */

#include "Motor.h"

Motor::Motor() {
	// TODO Auto-generated constructor stub

}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

void Motor::motor_on() {
	Motor::run_Right();
}

/*
 * stops motor by changing BIT_0 to 0, if the motor was already running
 */
void Motor::motor_off() {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, BIT_0 ^ portAState);
}

void Motor::run_right() {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, BIT_0 | portAState);
}

/*
 * this function isn't obligatory in our Software
 */
void Motor::run_left() {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, BIT_1 | portAState);
}

/*
 * this function isn't obligatory in our Software
 */
void Motor::run_slow() {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, BIT_2 | portAState);
}

/*
 * stops motor by changing BIT_3 to 0, the other bits stay unchanged
 */
void Motor::stop_Motor() {
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, BIT_3 | portAState);
}

