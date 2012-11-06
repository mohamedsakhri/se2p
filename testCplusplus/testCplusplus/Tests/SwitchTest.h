/*
 * SwitchTest.h
 *
 *  Created on:
 *      Author: simohamed
 */

#ifndef SWITCHTEST_H_
#define SWITCHTEST_H_
#include "HAWThread.h"
#include "Constants.h"

using namespace thread;
class SwitchTest: public HAWThread {
public:
	SwitchTest();
	virtual ~SwitchTest();
private:
	virtual void execute(void*arg);
	virtual void shutdown();
};

#endif /* SWITCHTEST_H_ */
