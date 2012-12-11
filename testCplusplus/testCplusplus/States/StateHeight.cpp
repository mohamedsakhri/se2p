/*
 * StateHeight.cpp
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#include "StateHeight.h"
#define DEBUG_


//-----------------WaitingHeightM1--------------

WaitingHeightM1::WaitingHeightM1(){
#ifdef DEBUG_
	cout << "WaitingHeightM1 Start constructur" << endl;
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
	(ControllerSeg2::getInstance()->getLastWP())->setIs_inTolleranceRange(true);
	cout << "get inTol after set inTol to true: " << ControllerSeg2::getInstance()->getLastWP()->getIs_inTolleranceRange() <<
			" WP: " <<  (ControllerSeg2::getInstance()->getLastWP())->getId() << endl;

	new (this) CheckDrill();
}

//-----------------TooSmall-------------

TooSmall::TooSmall(){
	cout << "Too small const" << endl;
}
TooSmall::~TooSmall(){

}

void TooSmall::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "TooSmall::outHeightMeasurement" << endl;
#endif

	//timer ??
	ControllerSeg2::getInstance()->passWP2Ctr();
	ControllerSeg2::getInstance()->removeLastWP();
	new (this) WaitingHeightM1();
}

//-------------------- CheckDrill-----------

CheckDrill::CheckDrill(){
	cout << "CheckDrill const" << endl;
}

CheckDrill::~CheckDrill(){

}

void CheckDrill::inHeightMeasurement(){
#ifdef DEBUG_
	cout << "CheckDrill::inHeightMeasurement" << endl;
#endif
	ControllerSeg2::getInstance()->getLastWP()->setHas_Drill(false);
	new (this) DrillChecked();
}


void CheckDrill::notInToleranceRange(){
#ifdef DEBUG_
	cout << "CheckDrill::notInToleranceRange " << endl;
#endif
	ControllerSeg2::getInstance()->getLastWP()->setHas_Drill(true);
	new (this) DrillChecked();
}



//-----------------DrillChecked--------------

DrillChecked::DrillChecked(){
	cout << "DrillChecked const" << endl;
}

DrillChecked::~DrillChecked(){

}

void DrillChecked::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "DrillChecked::outHeightMeasurement" << endl;
#endif

	// timer !!
	ControllerSeg2::getInstance()->passWP2Ctr();
	ControllerSeg2::getInstance()->removeLastWP();
	new (this) WaitingHeightM1();
}
