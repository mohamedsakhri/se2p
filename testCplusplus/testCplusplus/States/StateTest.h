/*
 * @file	StateTest.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Nov 11, 2012
 *
 * This class is used to test states' implementation.
 */

#ifndef STATETASTE_H_
#define STATETASTE_H_

#include "ControllerSeg1.h"
#include "ControllerSeg2.h"
#include "ControllerSeg3.h"
#include "ControllerSeg4.h"
#include "ControllerSeg5.h"
#include "ControllerSegM2.h"
#include "MainController.h"
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
