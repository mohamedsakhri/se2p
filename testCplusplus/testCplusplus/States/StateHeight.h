/*
 * StateHeight.h
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#ifndef STATEHEIGHT_H_
#define STATEHEIGHT_H_

#include "IState.h"
#include "ControllerSeg2.h"

//class ControllerSeg2;

using namespace std;

class WaitingHeightM1: public IState {
public:

	WaitingHeightM1();
	virtual ~WaitingHeightM1();
	void inHeightMeasurement();
	void inToleranceRange();
};


class CheckDrill: public IState {
public:
	CheckDrill();
	virtual ~CheckDrill();
	void inHeightMeasurement();
	void notInToleranceRange();
};

class DrillChecked: public IState{
public:
	DrillChecked();
	virtual ~DrillChecked();
	void outHeightMeasurement();
};

class TooSmall: public IState{
public:
	TooSmall();
	virtual ~TooSmall();
	void outHeightMeasurement();
};
#endif /* STATEHEIGHT_H_ */
