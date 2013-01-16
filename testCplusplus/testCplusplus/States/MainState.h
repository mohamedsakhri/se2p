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

/**
 * State when machine has started the first time. It is the "Start State".
 * In this state only Start-Button can be pressed to initialize machine.
 */
class InitState: public IState {
public:
	InitState();
	virtual ~InitState();

	//Start button has to be pressed to initialize machine
	void startPressed();

	//Buttons to be ignored
//	void startReleased(){};
//	void resetPressed(){};
//	void resetReleased(){};
//	void EStopPressed(){};
//	void EStopReleased(){};
};

/**
 * State when machine is running. In this state the machine is working normal.
 */
class RunningMachine: public IState {
public:
	RunningMachine();
	virtual ~RunningMachine();

	//Methods to control buttons
	void stopPressed();
	void resetPressed();
	void EStopPressed();

	//Methods to handle errors
	void timeOutError();
	void slideFull();
	void turningErrorHandling();

	//Buttons to be ignored
//	void EStopReleased(){};
//	void startPressed(){};
//	void startReleased(){};

};

/**
 * State when an error has occurred. The machine will be in this state in case of :
 * 1. Errors related to timer : A workpiece is missing or stranger
 * 2. Workpiece is not put back when it has to be turned in the end of machine1
 */
class ErrorHandling: public IState {
public:
	ErrorHandling();
	virtual ~ErrorHandling();

	//Methods to control buttons
	void startPressed();
	void resetPressed();

	//Buttons to be ignored
//	void EStopPressed(){};
//	void EStopReleased(){};
//	void startReleased(){};
};

/**
 * State when slide becomes full.
 */
class SlideHandling: public IState{
public:
	SlideHandling();
	virtual ~SlideHandling();

	void resetPressed();
	void slideErrorFixed();
};

/**
 * State when a Workpiece is not put back in line when it has to be turned in the end of machine1
 */
class TurningErrorHandling: public IState{
public:
	TurningErrorHandling();
	virtual ~TurningErrorHandling();

	void resetPressed();
	void startPressed();
	void inLineEnd();
};

/**
 * State when the machine is stopped after the stop button has been pressed
 */
class Stop: public IState {
public:
	Stop();
	virtual ~Stop();

	void startPressed();
};

/**
 * State when E-Stop button has been pressed.
 */
class Emergency: public IState {
public:
	Emergency();
	virtual ~Emergency();

	void EStopReleased();
};

/**
 * State when E-Stop button has been pulled out.
 * In this state only Reset button can be pressed.
 */
class WaitingForReset: public IState {
public:
	WaitingForReset();
	virtual ~WaitingForReset();

	void resetPressed();
};

#endif /*MAINSTATE_H_ */
