/*
 * WaitingSwitch.h
 *
 *  Created on: 07.12.2012
 *      Author: aax844
 */

#ifndef WAITINGSWITCH_H_
#define WAITINGSWITCH_H_

#include "IState.h"
#include "Controller.h"

using namespace std;

class WaitingSwitch: public IState {
public:
	WaitingSwitch(HALCallInterface* ctr);
	virtual ~WaitingSwitch();

	void inSwitch();
private:
	HALAktorik* hal_aktorik_;
};

class WorkPieceInvalid: public IState {
public:
	WorkPieceInvalid(HALCallInterface* ctr);
	virtual ~WorkPieceInvalid();

	void outSwitch();
private:
	HALAktorik* hal_aktorik_;
};

class WorkPieceValid: public IState {
public:
	WorkPieceValid(HALCallInterface* ctr);
	virtual ~WorkPieceValid();

	void outSwitch();
private:
	HALAktorik* hal_aktorik_;
};


#endif /* WAITINGSWITCH_H_ */
