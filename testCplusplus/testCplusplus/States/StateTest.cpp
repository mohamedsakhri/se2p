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

}

StateTest::~StateTest() {
	// TODO Auto-generated destructor stub
}


void StateTest::execute(void *arg)
{
	cout << "StateTaste started" << endl;

	ControllerSeg1 ctr1;
//	ControllerSeg1 ctr2;
//	ControllerSeg1 ctr3;



	// Controllers add some events to register to
	ctr1.addEvent(WP_IN_ENGINE_START);
	ctr1.addEvent(WP_OUT_ENGINE_START);

//	ctr2.addEvent(WP_IN_HEIGHT_M);
//	ctr2.addEvent(WP_OUT_HEIGHT_M);
//	ctr2.addEvent(WP_IN_TOLERANCE_R);
//	ctr2.addEvent(WP_NOT_IN_TOLERANCE_R);
//
//	ctr3.addEvent(WP_IN_SWITCH);
//	ctr3.addEvent(WP_OUT_SWITCH);
//
//	ctr3.addEvent(STOP_PRESSED);


	// Register Controllers for some events
	dispatcher_->registerHandler(&ctr1);
//	dispatcher_->registerHandler(&ctr2);
//	dispatcher_->registerHandler(&ctr3);
	dispatcher_->start(NULL);

	dispatcher_->join();

	cout << "StateTaste end" << endl;

}



void StateTest::shutdown()
{
}


