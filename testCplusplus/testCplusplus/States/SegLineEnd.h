/*
 * @file	SegLineEnd.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 5
 *
 */

#ifndef SEGLINEEND_H_
#define SEGLINEEND_H_

#include "IState.h"
#include "ControllerSeg1.h"
#include "ControllerSeg2.h"
#include "ControllerSeg3.h"
#include "ControllerSeg4.h"
#include "ControllerSeg5.h"
#include "MainController.h"
#include "LightFlash.h"
#include "Constants.h"


using namespace std;

/*
 *
 */
class WaitLineEndM1: public IState {
public:
	WaitLineEndM1();
	virtual ~WaitLineEndM1();

	void inLineEnd();
};

/*
 *
 */
class TransferMachine2: public IState {
public:
	TransferMachine2();
	virtual ~TransferMachine2();

	void machine2IsReady();

};

/*
 *
 */
class WaitForTurn: public IState {
public:
	WaitForTurn();
	virtual ~WaitForTurn();

	void outLineEnd();
};

/*
 *
 */
class Turning: public IState {
public:
	Turning();
	virtual ~Turning();

	void inLineEnd();
};

/*
 *
 */
class WaitForMachine2: public IState {
public:
	WaitForMachine2();
	virtual ~WaitForMachine2();

	void messageReceived();
};


/*
 *
 */
class Machine2Ready: public IState {
public:
	Machine2Ready();
	virtual ~Machine2Ready();

	void outLineEnd();
};


#endif /*SEGLINEEND_H_ */
