/*
 * StateTaste.h
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#ifndef STATETASTE_H_
#define STATETASTE_H_

#include "ControllerSeg1.h"
#include "ControllerSeg2.h"
#include "ControllerSeg3.h"
#include "HAWThread.h"
#include "Dispatcher.h"

class StateTest: public thread::HAWThread {
public:
	StateTest();
	virtual ~StateTest();

	void execute(void* arg);
	void shutdown();

private:
	Dispatcher* dispatcher_;
};

#endif /* STATETASTE_H_ */
