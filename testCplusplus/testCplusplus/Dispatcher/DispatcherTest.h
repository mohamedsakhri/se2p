/*
 * DispatcherTest.h
 *
 *  Created on: Nov 26, 2012
 *      Author: simohamed
 */

#ifndef DISPATCHERTEST_H_
#define DISPATCHERTEST_H_

#include "HAWThread.h"
#include "ControllerTest.h"
#include "Dispatcher.h"

class DispatcherTest: public thread::HAWThread {
public:
	DispatcherTest();
	virtual ~DispatcherTest();

	void execute(void* arg);
	void shutdown();
private :
	Dispatcher* dispatcher_;
};

#endif /* DISPATCHERTEST_H_ */
