/*
 * LEDTest.h
 *
 *  Created on:
 *      Author: simohamed
 */

#ifndef LEDTEST_H_
#define LEDTEST_H_
#include "HAWThread.h"

using namespace thread;
class LEDTest: public HAWThread {
public:
	LEDTest();
	virtual ~LEDTest();
private:
	virtual void execute(void*arg);
	virtual void shutdown();
};

#endif /* LEDTEST_H_ */
