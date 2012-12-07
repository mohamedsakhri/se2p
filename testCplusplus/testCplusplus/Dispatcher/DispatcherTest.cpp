/*
 * DispatcherTest.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: simohamed
 */

#include "DispatcherTest.h"
#include "Constants.h"

#define UNREGISTER_TEST

DispatcherTest::DispatcherTest() {
	dispatcher_ = Dispatcher::getInstance();
}

DispatcherTest::~DispatcherTest() {
	// TODO Auto-generated destructor stub
}

void DispatcherTest::execute(void *arg)
{
/*	cout << "DispatcherTest started" << endl;

	ControllerTest ctr;
	ControllerTest ctr_2;
	// Controllers add some events to register to
	ctr.addEvent(WP_IN_ENGINE_START);
	ctr.addEvent(STOP_PRESSED);

	ctr_2.addEvent(WP_IN_ENGINE_START);
	ctr_2.addEvent(WP_IN_ENGINE_END);
	ctr_2.addEvent(STOP_PRESSED);
	ctr_2.addEvent(WP_IS_MISSING);

	// Register Controllers for some events
	dispatcher_->registerHandler(&ctr);
	dispatcher_->registerHandler(&ctr_2);
	dispatcher_->start(NULL);

#ifdef UNREGISTER_TEST
	// Wait a while, than unregister ctr from Dispatcher
	WAIT_TEN_S;
	dispatcher_->removeHandler(&ctr);
#endif
	dispatcher_->join();

	cout << "DispatcherTest end" << endl;
*/
}



void DispatcherTest::shutdown()
{
}


