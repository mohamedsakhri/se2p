/*
 * @file	SegHeight.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 2
 *
 */

#ifndef SEGHEIGHT_H_
#define SEGHEIGHT_H_

#include "IState.h"
#include "ControllerSeg2.h"

//class ControllerSeg2;

using namespace std;
/*
 *
 */
class WaitingHeightM1: public IState {
public:

	WaitingHeightM1();
	virtual ~WaitingHeightM1();

	void inHeightMeasurement();
	void inToleranceRange();
};

/*
 *
 */
class CheckDrill: public IState {
public:
	CheckDrill();
	virtual ~CheckDrill();

	void outHeightMeasurement();
	void inToleranceRange();
};

/*
 *
 */
//class DrillChecked: public IState{
//public:
//	DrillChecked();
//	virtual ~DrillChecked();
//
//	void outHeightMeasurement();
//};

/*
 *
 */
class TooSmall: public IState{
public:
	TooSmall();
	virtual ~TooSmall();

	void outHeightMeasurement();
};

#endif /* SEGHEIGHT_H__ */
