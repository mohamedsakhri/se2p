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
	ControllerSeg4 *ctr4 = ControllerSeg4::getInstance();
	ControllerSeg5 *ctr5 = ControllerSeg5::getInstance();

	// Controllers add some events to register to
	ctr1->addEvent(WP_IN_ENGINE_START);
	ctr1->addEvent(WP_OUT_ENGINE_START);
	ctr1->addEvent(START_PRESSED);
	ctr1->addEvent(STOP_PRESSED);
	ctr1->addEvent(E_STOP_PRESSED);
	ctr1->addEvent(E_STOP_RELEASED);

	ctr2->addEvent(WP_IN_HEIGHT_M);
	ctr2->addEvent(WP_OUT_HEIGHT_M);
	ctr2->addEvent(WP_IN_TOLERANCE_R);
	ctr2->addEvent(WP_NOT_IN_TOLERANCE_R);
	ctr2->addEvent(START_PRESSED);
	ctr2->addEvent(STOP_PRESSED);
	ctr2->addEvent(E_STOP_PRESSED);
	ctr2->addEvent(E_STOP_RELEASED);


	ctr3->addEvent(WP_IN_SWITCH);
	ctr3->addEvent(WP_OUT_SWITCH);
	ctr3->addEvent(START_PRESSED);
	ctr3->addEvent(STOP_PRESSED);
	ctr3->addEvent(E_STOP_PRESSED);
	ctr3->addEvent(E_STOP_RELEASED);


	ctr4->addEvent(WP_IN_SLIDE);
	ctr4->addEvent(WP_OUT_SLIDE);
	ctr4->addEvent(START_PRESSED);
	ctr4->addEvent(STOP_PRESSED);
	ctr4->addEvent(E_STOP_PRESSED);
	ctr4->addEvent(E_STOP_RELEASED);


	ctr5->addEvent(WP_IN_ENGINE_END);
	ctr5->addEvent(WP_OUT_ENGINE_END);
	ctr5->addEvent(START_PRESSED);
	ctr5->addEvent(STOP_PRESSED);
	ctr5->addEvent(E_STOP_PRESSED);
	ctr5->addEvent(E_STOP_RELEASED);


//	ctr3->addEvent(STOP_PRESSED);


	// Register Controllers for some events
	dispatcher_->registerHandler(ctr1);
	dispatcher_->registerHandler(ctr2);
	dispatcher_->registerHandler(ctr3);
	dispatcher_->registerHandler(ctr4);
	dispatcher_->registerHandler(ctr5);

	dispatcher_->start(NULL);

	dispatcher_->join();

//	cout << "StateTaste end" << endl;

}



void StateTest::shutdown()
{
}


