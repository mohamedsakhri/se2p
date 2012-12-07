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

WaitingHeightM1::WaitingHeightM1(HALCallInterface* ctr){
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

	new (this) TooSmall(controller);
}

void WaitingHeightM1::inToleranceRange(){
#ifdef DEBUG_
	cout << "WaitingHeightM1->inToleranceRange" << endl;
#endif
	//TODO WP's Id !!
//	WorkPiece wp(1) ;
	WorkPiece wp = controller->getLastWP();
	wp.setIs_inTolleranceRange(true);
	controller->addWP2List(wp);

	new (this) CheckDrill(controller);
}

//-----------------TooSmall-------------

TooSmall::TooSmall(HALCallInterface* ctr){
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
	new (this) WaitingHeightM1(controller);
}

//-------------------- CheckDrill-----------

CheckDrill::CheckDrill(HALCallInterface* ctr){
	this->controller = ctr;
	hal_aktorik_ = HALAktorik::getInstance();
}

CheckDrill::~CheckDrill(){

}

void CheckDrill::inHeightMeasurement(){
#ifdef DEBUG_
	cout << "CheckDrill::inHeightMeasurement" << endl;
#endif
	controller->getLastWP().setHas_Drill(false);
	new (this) DrillChecked(controller);
}


void CheckDrill::notInToleranceRange(){
#ifdef DEBUG_
	cout << "CheckDrill::notInToleranceRange " << endl;
#endif
	controller->getLastWP().setHas_Drill(true);
	new (this) DrillChecked(controller);
}



//-----------------DrillChecked--------------

DrillChecked::DrillChecked(HALCallInterface* ctr){
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
	controller->removeLastWP();
	new (this) WaitingHeightM1(controller);
}
