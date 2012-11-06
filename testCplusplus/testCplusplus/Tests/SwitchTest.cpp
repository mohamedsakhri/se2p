/*
 * SwitchTest.cpp
 *
 *  Created on:
 *      Author: simohamed
 */

#include "SwitchTest.h"
#include <unistd.h>
#include "HALAktorik.h"

SwitchTest::SwitchTest() {
	// TODO Auto-generated constructor stub

}

SwitchTest::~SwitchTest() {
	// TODO Auto-generated destructor stub
}

void SwitchTest::execute(void *arg) {
	HALAktorik *hal_A = HALAktorik::getInstance();

	hal_A->open_Switch();
	cout << "Switch open" << endl;
	WAIT_THREE_S;
	hal_A->close_Switch();
	cout << "Switch closed" << endl;


}

void SwitchTest::shutdown() {
}

