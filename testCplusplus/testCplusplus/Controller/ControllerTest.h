/*
 * @file	ControllerTest.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	Nov 26, 2012
 *
 *	Class created to be used in dispatcherTest. The events hander work directly with HALAktorik because the test has to be
 *	implemented before States machine are implemented.
 *
 */

#ifndef CONTROLLERTEST_H_
#define CONTROLLERTEST_H_

#include "HALCallInterface.h"
#include "HALAktorik.h"
#include "Dispatcher.h"

class ControllerTest: public HALCallInterface {
public:
	ControllerTest();

	void inLineStart();
	void outLineStart();
	void inHeightMeasurement();
	void outHeightMeasurement();
	void inToleranceRange();
	void notInToleranceRange();
	void isMetal();
	void notMetal();
	void inSwitch();
	void outSwitch();
	void switchOpen();
	void switchClosed();
	void inSlide();
	void outSlide();
	void inLineEnd();
	void outLineEnd();

	void startPressed();
	void startReleased();
	void stopPressed();
	void stopReleased();
	void resetPressed();
	void resetReleased();
	void EStopPressed();
	void EStopReleased();

	// Error handling. Not needed here
	void isMissing();
	int sendMsg2Dispatcher(int message);
	void init();

	int getControllerId();
	void passWP2Ctr();

	virtual ~ControllerTest();

private:
	static int ctr_number_;		//!< Controller's number. Needed to assign an id to each new one
	// HALaktoric's instance now just for Dispatcher test
	HALAktorik* hal_aktorik_;
	Dispatcher* dispatcher_;
	Demultiplexer* demultiplexer_;
};

#endif /* CONTROLLER_H_ */
