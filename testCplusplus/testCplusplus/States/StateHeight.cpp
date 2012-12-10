/*
 * StateHeight.cpp
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#include "StateHeight.h"
#include <iostream>
#define DEBUG_


//-----------------WaitingHeightM1--------------

WaitingHeightM1::WaitingHeightM1(){
	this->controller = ctr;
	hal_aktorik_ = HALAktorik::getInstance();
}

WaitingHeightM1::~WaitingHeightM1() {

}

void WaitingHeightM1::inHeightMeasurement(){
#ifdef DEBUG_
	cout << "WaitingHeightM1::inHeightMeasurement" << endl;
#endif
//	WorkPiece wp(1) ;
//	controller->addWP2List(wp);

	new (this) TooSmall();
}

void WaitingHeightM1::inToleranceRange(){
#ifdef DEBUG_
	cout << "WaitingHeightM1->inToleranceRange" << endl;
#endif
	//TODO WP's Id !!
//	WorkPiece wp(1) ;
	WorkPiece wp = ControllerSeg2::getInstance()->getLastWP();
	wp.setIs_inTolleranceRange(true);
	ControllerSeg2::getInstance()->addWP2List(wp);

	new (this) CheckDrill();
}

//-----------------TooSmall-------------

TooSmall::TooSmall(){
	this->controller = ctr;
	hal_aktorik_ = HALAktorik::getInstance();

}
TooSmall::~TooSmall(){

}

void TooSmall::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "TooSmall::outHeightMeasurement" << endl;
#endif
	//timer ??
	new (this) WaitingHeightM1();
}

//-------------------- CheckDrill-----------

CheckDrill::CheckDrill(){
	this->controller = ctr;
	hal_aktorik_ = HALAktorik::getInstance();
}

CheckDrill::~CheckDrill(){

}

void CheckDrill::inHeightMeasurement(){
#ifdef DEBUG_
	cout << "CheckDrill::inHeightMeasurement" << endl;
#endif
	ControllerSeg2::getInstance()->getLastWP().setHas_Drill(false);
	new (this) DrillChecked();
}


void CheckDrill::notInToleranceRange(){
#ifdef DEBUG_
	cout << "CheckDrill::notInToleranceRange " << endl;
#endif
	ControllerSeg2::getInstance()->getLastWP().setHas_Drill(true);
	new (this) DrillChecked();
}



//-----------------DrillChecked--------------

DrillChecked::DrillChecked(){
	this->controller = ctr;
	hal_aktorik_ = HALAktorik::getInstance();
}

DrillChecked::~DrillChecked(){

}

void DrillChecked::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "DrillChecked::outHeightMeasurement" << endl;
#endif

	// timer !!
	ControllerSeg2::getInstance()->removeLastWP();
	new (this) WaitingHeightM1();
}
