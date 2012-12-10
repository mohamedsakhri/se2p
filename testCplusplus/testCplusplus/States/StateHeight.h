/*
 * StateHeight.h
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#ifndef STATEHEIGHT_H_
#define STATEHEIGHT_H_

#include "IState.h"
#include "HALAktorik.h"

using namespace std;

class WaitingHeightM1: public IState {
public:

	WaitingHeightM1();
	virtual ~WaitingHeightM1();
	void inHeightMeasurement();
	void inToleranceRange();
private:
	HALAktorik* hal_aktorik_;
};


class CheckDrill: public IState {
public:
	CheckDrill();
	virtual ~CheckDrill();
	void inHeightMeasurement();
	void notInToleranceRange();
private:
	HALAktorik* hal_aktorik_;
};

class DrillChecked: public IState{
public:
	DrillChecked();
	virtual ~DrillChecked();
	void outHeightMeasurement();
private:
	HALAktorik* hal_aktorik_;
};

class TooSmall: public IState{
public:
	TooSmall();
	virtual ~TooSmall();
	void outHeightMeasurement();
private:
	HALAktorik* hal_aktorik_;
};
#endif /* STATEHEIGHT_H_ */
