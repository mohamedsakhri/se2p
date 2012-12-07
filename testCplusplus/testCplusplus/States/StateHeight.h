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
#include "Controller.h"

using namespace std;

class WaitingHeightM1: public IState {
public:

	WaitingHeightM1(HALCallInterface* ctr);
	virtual ~WaitingHeightM1();
	void inHeightMeasurement();
	void inToleranceRange();
private:
	HALAktorik* hal_aktorik_;
};


class CheckDrill: public IState {
public:
	CheckDrill(HALCallInterface* ctr);
	virtual ~CheckDrill();
	void inHeightMeasurement();
	void notInToleranceRange();
private:
	HALAktorik* hal_aktorik_;
};

class DrillChecked: public IState{
public:
	DrillChecked(HALCallInterface* ctr);
	virtual ~DrillChecked();
	void outHeightMeasurement();
private:
	HALAktorik* hal_aktorik_;
};

class TooSmall: public IState{
public:
	TooSmall(HALCallInterface* ctr);
	virtual ~TooSmall();
	void outHeightMeasurement();
private:
	HALAktorik* hal_aktorik_;
};
#endif /* STATEHEIGHT_H_ */
