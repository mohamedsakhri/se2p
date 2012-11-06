/*
 * LightTest.cpp
 *
 *  Created on:
 *      Author: simohamed
 */

#include "LightTest.h"
#include <unistd.h>
#include "HALAktorik.h"
#include "Constants.h"
#include "RedLightFlash.h"

#define QUICK 500000
#define SLOW 1000000

#define FLASH_TEST

LightTest::LightTest() {
	// TODO Auto-generated constructor stub

}

LightTest::~LightTest() {
	// TODO Auto-generated destructor stub
}

void LightTest::execute(void *arg) {


#ifdef LIGHT_TEST
	HALAktorik *hal_A = HALAktorik::getInstance();
	hal_A->red_Light_on();
	cout << "Red light on " << endl;
	WAIT_THREE_S;

	hal_A->red_Light_off();
	cout << "Red light off " << endl;
	WAIT_THREE_S;

	hal_A->yellow_Light_on();
	cout << "Yellow light on " << endl;
	WAIT_THREE_S;

	hal_A->yellow_Light_off();
	cout << "Yellow light off " << endl;
	WAIT_THREE_S;

	hal_A->green_Light_on();
	cout << "Green light on " << endl;
	WAIT_THREE_S;

	hal_A->green_Light_off();
	cout << "Green light off " << endl;
	WAIT_THREE_S;
#endif /*LIGHT_TEST*/

#ifdef FLASH_TEST
	RedLightFlash flashTest;
	int seeptime = SLOW;			//sleeptime for slow blinking

	cout << "START flashing test " << endl;
	flashTest.start(&seeptime);
	WAIT_FIVE_S;
	flashTest.stop();
	cout << "END flashing test " << endl;
	flashTest.join();

#endif  /*FLASH_TEST*/

}

void LightTest::shutdown() {
}

