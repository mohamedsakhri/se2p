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

	Controller ctr;
	// Controllers add some events to register to
	ctr.addEvent(WP_IN_ENGINE_START);
	ctr.addEvent(WP_OUT_ENGINE_START);
	ctr.addEvent(WP_IN_HEIGHT_M);
	ctr.addEvent(WP_OUT_HEIGHT_M);
	ctr.addEvent(WP_IN_TOLERANCE_R);


	// Register Controllers for some events
	dispatcher_->registerHandler(&ctr);
	dispatcher_->start(NULL);

#ifdef UNREGISTER_TEST
	// Wait a while, than unregister ctr from Dispatcher
	WAIT_TEN_S;
	dispatcher_->removeHandler(&ctr);
#endif
	dispatcher_->join();

	cout << "StateTaste end" << endl;

}



void StateTest::shutdown()
{
}


