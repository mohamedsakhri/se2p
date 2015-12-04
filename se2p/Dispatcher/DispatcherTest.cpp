/*
 * DispatcherTest.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: simohamed
 */

#include "DispatcherTest.h"
#include "Constants.h"

#define DEBUG_

DispatcherTest::DispatcherTest() {
	dispatcher_ = Dispatcher::getInstance();
}

DispatcherTest::~DispatcherTest() {
	// TODO Auto-generated destructor stub
}

void DispatcherTest::execute(void *arg)
{
#ifdef DEBUG_
	cout << "DispatcherTest started" << endl;
#endif

	ControllerTest ctr;
	ControllerTest ctr_2;

	// Controllers add some events to register to
	ctr.addEvent(WP_IN_ENGINE_START);
	ctr.addEvent(STOP_PRESSED);
	ctr.addEvent(WP_IN_SWITCH);
	ctr.addEvent(WP_OUT_SWITCH);
	ctr.addEvent(WP_NOT_IN_TOLERANCE_R);
	ctr.addEvent(WP_IN_TOLERANCE_R);
	ctr.addEvent(WP_IN_ENGINE_END);

	ctr_2.addEvent(WP_IN_ENGINE_START);
	ctr_2.addEvent(WP_IN_ENGINE_END);
	ctr_2.addEvent(STOP_PRESSED);
	ctr_2.addEvent(WP_IS_MISSING);

	// Register Controllers in Dispatcher for some events
	dispatcher_->registerHandler(&ctr);
	dispatcher_->registerHandler(&ctr_2);
	dispatcher_->start(NULL);

	dispatcher_->join();

#ifdef DEBUG_
	cout << "DispatcherTest End" << endl;
#endif


}



void DispatcherTest::shutdown()
{
}


