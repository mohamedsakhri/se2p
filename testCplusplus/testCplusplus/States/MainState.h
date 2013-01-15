/*
 * @file	MainState.h
 *
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 19, 2012
 *
 * Classes which represent the main state
 *
 */

#ifndef MAINSTATE_H_
#define MAINSTATE_H_

#include "IState.h"
#include "Dispatcher.h"
#include "ControllerSeg1.h"
#include "ControllerSeg2.h"
#include "ControllerSeg3.h"
#include "ControllerSeg4.h"
#include "ControllerSeg5.h"
#include "MainController.h"



using namespace std;

/*
 *
 */
class InitState: public IState {
public:
	InitState();
	virtual ~InitState();

	void startPressed();
};

/*
 *
 */
class RunningMachine1: public IState {
public:
	RunningMachine1();
	virtual ~RunningMachine1();

	void stopPressed();
	void resetPressed();
	void EStopPressed();
	void timeOutError();
	void slideFull();
	void startPressed(){};
	void startReleased(){};
};

/*
 *
 */
class ErrorHandling: public IState {
public:
	ErrorHandling();
	virtual ~ErrorHandling();

	void startPressed();
	void resetPressed();
};

/*
 *
 */
class SlideHandling: public IState{
public:
	SlideHandling();
	virtual ~SlideHandling();

	void resetPressed();
	void slideErrorFixed();
};

/*
 *
 */
class Stop: public IState {
public:
	Stop();
	virtual ~Stop();

	void startPressed();
};

/*
 *
 */
class Emergency: public IState {
public:
	Emergency();
	virtual ~Emergency();

	//TODO Only Reset is allowed when EStop released
	void EStopReleased();
};

/*
 *
 */
class WaitingForReset: public IState {
public:
	WaitingForReset();
	virtual ~WaitingForReset();

	void ResetPressed();
};


#endif /*MAINSTATE_H_ */
