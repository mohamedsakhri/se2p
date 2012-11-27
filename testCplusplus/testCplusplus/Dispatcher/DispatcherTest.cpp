/*
 * DispatcherTest.cpp
 *
 *  Created on: Nov 26, 2012
 *      Author: simohamed
 */

#include "DispatcherTest.h"

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
	ctr.addEvent(WP_IN_ENGINE_START);
	ctr.addEvent((WP_IN_HEIGHT_M));
	dispatcher_->registerHandler(&ctr);
	dispatcher_->start(NULL);
	dispatcher_->join();

	cout << "DispatcherTest end" << endl;


}



void DispatcherTest::shutdown()
{
	dispatcher_->join();
}


