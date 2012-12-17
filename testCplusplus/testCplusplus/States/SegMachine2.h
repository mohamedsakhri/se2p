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
#include "ControllerSegM2.h"
#include "Constants.h"
#include "Messages.h"






//************************* WaitForLinestart ***************************
class WaitForLineStart:public IState {
public :
	WaitForLineStart();
	virtual ~WaitForLineStart();

	void wpIsComming();
};

//************************* wpIsComming ***************************
class WpIsComming:public IState {
public :
	WpIsComming();
	virtual ~WpIsComming();

	void inLineStart();
};


//************************* WaitForHeightM2 ***************************
class WaitForHeightM2:public IState {
public :
	WaitForHeightM2();
	virtual ~WaitForHeightM2();

	void inHeightMeasurement();
	void inToleranceRange();
};

//************************* noDrill ***************************
//TODO error (if drill down or small WP)
class NoDrill:public IState {
public :
	NoDrill();
	virtual ~NoDrill();

};


//************************* CheckDrill ***************************

class CheckDrillM2: public IState{
public:
	CheckDrillM2();
	virtual ~CheckDrillM2();

	void outHeightMeasurement();
	void inToleranceRange();
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
public:
	HasMetall();
	virtual ~HasMetall();

	void inSwitch();
};

//************************* WorkPieceIsInvalid ***************************
class WorkPieceIsInvalid: public IState {
public:
	WorkPieceIsInvalid();
	virtual ~WorkPieceIsInvalid();

	void outSwitch();
};

//************************* InSlide ***************************
class InSlideM2: public IState {
public:
	InSlideM2();
	virtual ~InSlideM2();

	void outSlide();
};

//************************* WorkPieceIsValid ***********************
class WorkPieceIsValid: public IState {
public:
	WorkPieceIsValid();
	virtual ~WorkPieceIsValid();

	void outSwitch();
};

//************************* WaitForEndLine ***********************
class WaitForEndLine: public IState {
public:
	WaitForEndLine();
	virtual ~WaitForEndLine();

	void outLineEnd();
};

#endif /* STATEMACHINE2_H_ */

