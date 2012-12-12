/*
 * @file	SegHeight.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 2
 *
 */

#include "SegHeight.h"
#define DEBUG_

/************************************************************************************
 *									WaitingHeighM1									*
 *																					*
 ************************************************************************************/

WaitingHeightM1::WaitingHeightM1(){
#ifdef DEBUG_
	cout << "WaitingHeightM1 Start constructor" << endl;
#endif
}

WaitingHeightM1::~WaitingHeightM1() {

}

void WaitingHeightM1::inHeightMeasurement(){
#ifdef DEBUG_
	cout << "WaitingHeightM1::inHeightMeasurement" << endl;
#endif

	new (this) TooSmall();
}

void WaitingHeightM1::inToleranceRange(){
#ifdef DEBUG_
	cout << "WaitingHeightM1->inToleranceRange" << endl;
#endif
	//TODO WP's Id !!
	(ControllerSeg2::getInstance()->getFirstWP())->setIs_inTolleranceRange(true);
#ifdef DEBUG_
	cout << "get inTol after set inTol to true: " << ControllerSeg2::getInstance()->getFirstWP()->getIs_inTolleranceRange() <<
			" WP: " <<  (ControllerSeg2::getInstance()->getFirstWP())->getId() << endl;
#endif

	new (this) CheckDrill();
}


/************************************************************************************
 *									TooSmall										*
 *																					*
 ************************************************************************************/

TooSmall::TooSmall(){
	cout << "Too small constructor" << endl;
}

TooSmall::~TooSmall(){

}

void TooSmall::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "TooSmall::outHeightMeasurement" << endl;
#endif
	// Start timer ??
	if (!ControllerSeg2::getInstance()->isFifoEmpty()) {
		ControllerSeg2::getInstance()->passWP2Ctr();
		ControllerSeg2::getInstance()->removeFirsttWP();

		new (this) WaitingHeightM1();
	} else {
		//TODO  just send msg and let controller do the rest according to the error event handler
		ControllerSeg2::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->red_Light_on();
		HALAktorik::getInstance()->green_Light_off();
	}
}


/************************************************************************************
 *									CheckDrill										*
 *																					*
 ************************************************************************************/

CheckDrill::CheckDrill(){
	cout << "CheckDrill constructor" << endl;
}

CheckDrill::~CheckDrill(){

}

void CheckDrill::inHeightMeasurement(){
#ifdef DEBUG_
	cout << "CheckDrill::inHeightMeasurement" << endl;
#endif

	ControllerSeg2::getInstance()->getFirstWP()->setHas_Drill(false);

	new (this) DrillChecked();
}


void CheckDrill::notInToleranceRange(){
#ifdef DEBUG_
	cout << "CheckDrill::notInToleranceRange " << endl;
#endif

	ControllerSeg2::getInstance()->getFirstWP()->setHas_Drill(true);
	new (this) DrillChecked();
}



/************************************************************************************
 *									DrillChecked									*
 *																					*
 ************************************************************************************/

DrillChecked::DrillChecked(){
	cout << "DrillChecked constructor" << endl;
}

DrillChecked::~DrillChecked(){

}

void DrillChecked::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "DrillChecked::outHeightMeasurement" << endl;
#endif
	// Start timer ??
	if (!ControllerSeg2::getInstance()->isFifoEmpty()) {
		ControllerSeg2::getInstance()->passWP2Ctr();
		ControllerSeg2::getInstance()->removeFirsttWP();

		new (this) WaitingHeightM1();
	} else {
		//TODO  just send msg and let controller do the rest according to the error event handler
		ControllerSeg2::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->red_Light_on();
		HALAktorik::getInstance()->green_Light_off();
	}
}

