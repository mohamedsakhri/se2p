/*
 * LEDTest.cpp
 *
 *  Created on:
 *      Author: simohamed
 */

#include "LEDTest.h"
#include <unistd.h>
#include "HALAktorik.h"
#include "Constants.h"

LEDTest::LEDTest() {
	// TODO Auto-generated constructor stub

}

LEDTest::~LEDTest() {
	// TODO Auto-generated destructor stub
}

void LEDTest::execute(void *arg) {

	HALAktorik *hal_A = HALAktorik::getInstance();

	hal_A->Q1_LED_on();
	cout << "Q1_LED on " << endl;
	WAIT_THREE_S;
	hal_A->Q1_LED_off();
	cout << "Q1_LED off " << endl;
	WAIT_THREE_S;
	hal_A->Q2_LED_on();
	cout << "Q2_LED on " << endl;
	WAIT_THREE_S;
	hal_A->Q2_LED_off();
	cout << "Q2_LED off " << endl;
	WAIT_THREE_S;
	hal_A->Reset_LED_on();
	cout << "Reset_LED on " << endl;
	WAIT_THREE_S;
	hal_A->Reset_LED_off();
	cout << "Reset_LED off " << endl;
	WAIT_THREE_S;
	hal_A->Start_LED_on();
	cout << "Start_LED on " << endl;
	WAIT_THREE_S;
	hal_A->Start_LED_off();
	cout << "Start_LED off " << endl;
	WAIT_THREE_S;
}

void LEDTest::shutdown() {
}

