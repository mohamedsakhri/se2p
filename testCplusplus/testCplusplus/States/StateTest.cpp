/*
 * StateTaste.cpp
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#include "StateTest.h"
#include "Constants.h"

StateTest::StateTest() {
	dispatcher_ = Dispatcher::getInstance();
	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->close_Switch();

}

StateTest::~StateTest() {
	// TODO Auto-generated destructor stub
}


void StateTest::execute(void *arg)
{
	cout << "StateTaste started" << endl;

	ControllerSeg1 *ctr1 = ControllerSeg1::getInstance();
	ControllerSeg2 *ctr2 = ControllerSeg2::getInstance();
	ControllerSeg3 *ctr3 = ControllerSeg3::getInstance();


	// Controllers add some events to register to
	ctr1->addEvent(WP_IN_ENGINE_START);
	ctr1->addEvent(WP_OUT_ENGINE_START);

	ctr2->addEvent(WP_IN_HEIGHT_M);
	ctr2->addEvent(WP_OUT_HEIGHT_M);
	ctr2->addEvent(WP_IN_TOLERANCE_R);
	ctr2->addEvent(WP_NOT_IN_TOLERANCE_R);

	ctr3->addEvent(WP_IN_SWITCH);
	ctr3->addEvent(WP_OUT_SWITCH);

//	ctr3->addEvent(STOP_PRESSED);


	// Register Controllers for some events
	dispatcher_->registerHandler(ctr1);
	dispatcher_->registerHandler(ctr2);
	dispatcher_->registerHandler(ctr3);
	dispatcher_->start(NULL);
//	while(1){}

	dispatcher_->join();

//	cout << "StateTaste end" << endl;

}



void StateTest::shutdown()
{
}


