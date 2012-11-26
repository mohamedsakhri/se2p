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
	dispatcher_->start(NULL);
}



void DispatcherTest::shutdown()
{
	dispatcher_->join();
}


