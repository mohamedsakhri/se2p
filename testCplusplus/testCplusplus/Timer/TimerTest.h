/*
 * @file	TimerTest.h
 *
 * @author	Martin Hepke
 *
 * @date	 Dec 14, 2012
 *
 * This class is used to test the Software's timer
 */

#ifndef TIMERTEST_H_
#define TIMERTEST_H_

#include "HAWThread.h"
#include "Dispatcher.h"

class TimerTest: public thread::HAWThread {
public:
	TimerTest();
	virtual ~TimerTest();
	void execute(void* arg);
	void shutdown();
};

#endif /* TIMERTEST_H_ */
