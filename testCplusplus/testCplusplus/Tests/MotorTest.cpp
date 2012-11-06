/*
 * MotorTest.cpp
 *
 *  Created on:
 *      Author: simohamed
 */

#include "MotorTest.h"
#include <unistd.h>
#include "HALAktorik.h"
#include "Constants.h"

MotorTest::MotorTest() {
	// TODO Auto-generated constructor stub

}

MotorTest::~MotorTest() {
	// TODO Auto-generated destructor stub
}

void MotorTest::execute(void *arg) {
	HALAktorik *hal_A = HALAktorik::getInstance();
	hal_A->motor_on();
	cout << "Motor on " << endl;
	WAIT_TEN_S;
	hal_A->motor_off();
	cout << "Motor off " << endl;
}

void MotorTest::shutdown() {
}

