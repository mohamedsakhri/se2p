/*
 * DispatcherTest.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: simohamed
 */

#include "DispatcherTest.h"
#include "Constants.h"

DispatcherTest::DispatcherTest() {
	dispatcher_ = Dispatcher::getInstance();
}

DispatcherTest::~DispatcherTest() {
	// TODO Auto-generated destructor stub
}

void DispatcherTest::execute(void *arg)
{
	cout << "DispatcherTest started" << endl;

	Controller ctr;
	Controller ctr_2;
	ctr.addEvent(WP_IN_ENGINE_START);
	ctr.addEvent((WP_IN_HEIGHT_M));
	ctr_2.addEvent(WP_IN_ENGINE_START);
	ctr_2.addEvent(WP_IN_ENGINE_END);
	dispatcher_->registerHandler(&ctr);
	dispatcher_->registerHandler(&ctr_2);
	dispatcher_->start(NULL);

	sleep(WAIT_FIVE_S);
	dispatcher_->removeHandler(&ctr);
	dispatcher_->join();

	cout << "DispatcherTest end" << endl;


}



void DispatcherTest::shutdown()
{
	dispatcher_->join();
}


