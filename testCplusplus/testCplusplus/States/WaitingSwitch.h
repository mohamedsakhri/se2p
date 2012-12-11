/*
 * WaitingSwitch.h
 *
 *  Created on: 07.12.2012
 *      Author: aax844
 */

#ifndef WAITINGSWITCH_H_
#define WAITINGSWITCH_H_

#include "IState.h"
#include "HALAktorik.h"
#include <iostream>
#include "ControllerSeg3.h"

using namespace std;

class WaitingSwitch: public IState {
public:
	WaitingSwitch();
	virtual ~WaitingSwitch();

	void inSwitch();
};

class WorkPieceInvalid: public IState {
public:
	WorkPieceInvalid();
	virtual ~WorkPieceInvalid();

	void outSwitch();
};

class WorkPieceValid: public IState {
public:
	WorkPieceValid();
	virtual ~WorkPieceValid();

	void outSwitch();
};


#endif /* WAITINGSWITCH_H_ */
