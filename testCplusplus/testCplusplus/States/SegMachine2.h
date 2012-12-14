/*
 * @file	SegMachine2.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent machine 2
 *
 */


#ifndef STATEMACHINE2_H_
#define STATEMACHINE2_H_

#include "IState.h"
#include "ControllerSeg1.h"
#include "ControllerSeg2.h"
#include "ControllerSeg3.h"
#include "ControllerSeg4.h"
#include "ControllerSeg5.h"

class SegMachine2:public IState {
public:
	SegMachine2();
	virtual ~SegMachine2();


};

//************************* inLineStart ***************************

class StateLineStart2:public Istate{
public :
	StateLineStart2();
	virtual ~StateLineStart2();

	void inLineStart();
};

//************************* WaitForHeightM2 ***************************

class WaitForHeightM2:public IState {
public :
	WaitForHeightM2();
	virtual ~WaitForHeightM2();

	void inHeightMeasurement();
	void inTolerance();
};

//************************* noDrill ***************************
//TODO error (if drill down or small WP)
class NoDrill:public IState {
public :
	NoDrill();
	virtual ~noDrill();

};


//************************* CheckDrill ***************************

class CheckDrill: public IState{
public:
	CheckDrill();
	virtual ~ CheckDrill();

	void outHeightMeasurement();
	void inTolerance();
};

//************************* DrillOkay ***************************

class DrillOkay: public IState {
public:
	DrillOkay();
	virtual ~DrillOkay();

	void outHeightMeasurement();
};

//************************* WaitForMetal ***************************

class WaitForMetal: public IState {
public:
	WaitForMetal();
	virtual ~WaitForMetal();

	void inSwitch();
	void isMetal();
};

//************************* HasMetal ***************************
class HasMetall: public IState {
	HasMetall();
	virtual ~HasMetall();

	void inSwitch();
};

//************************* WorkPieceIsInvalid ***************************
class WorkPieceIsInvalid: public IState {
	WorkPieceIsInvalid();
	virtual ~WorkPieceIsInvalid();

	void outSwitch();
};

//************************* InSlide ***************************
class InSlide: public IState {
	InSlide();
	virtual ~InSlide();

	void outSlide();
};

//************************* WorkPieceIsValid ***********************
class WorkPieceIsValid: public IState {
	WorkPieceIsValid();
	virtual ~WorkPieceIsValid();

	void outSwitch();
};

//************************* WaitForEndLine ***********************
class WaitForEndLine: public IState {
	WaitForEndLine();
	virtual ~WaitForEndLine();

	void inLineEnd();
};

#endif /* STATEMACHINE2_H_ */

