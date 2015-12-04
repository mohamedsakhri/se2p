/*
 * LightTest.h
 *
 *  Created on:
 *      Author: simohamed
 */

#ifndef LIGHTTEST_H_
#define LIGHTTEST_H_
#include "HAWThread.h"

using namespace thread;

class LightTest: public HAWThread {
public:
	LightTest();
	virtual ~LightTest();
private:
	virtual void execute(void*arg);
	virtual void shutdown();
};

#endif /* LIGHTTEST_H_ */
