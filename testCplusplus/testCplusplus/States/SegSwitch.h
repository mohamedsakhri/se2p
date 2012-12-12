/*
 * @file	SegSwitch.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 3
 *
 */

#ifndef WAITINGSWITCH_H_
#define WAITINGSWITCH_H_

#include "IState.h"
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


#endif /*SEGSWITCH_H_ */
