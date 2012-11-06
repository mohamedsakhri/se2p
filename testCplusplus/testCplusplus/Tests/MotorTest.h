/*
 * MotorTest.h
 *
 *  Created on:
 *      Author: simohamed
 */

#ifndef MOTORTEST_H_
#define MOTORTEST_H_
#include "HAWThread.h"

using namespace thread;
class MotorTest: public HAWThread {
public:
	MotorTest();
	virtual ~MotorTest();
private:
	virtual void execute(void*arg);
	virtual void shutdown();
};

#endif /* MOTORTEST_H_ */
