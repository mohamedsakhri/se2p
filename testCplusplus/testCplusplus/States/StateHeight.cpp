/*
 * StateHeight.cpp
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#include "StateHeight.h"
#include <iostream>
#define DEBUG_

WaitingHeightM1::WaitingHeightM1() {
	hal_aktorik_ = HALAktorik::getInstance();

}

CheckDrill::CheckDrill(){
	hal_aktorik_ = HALAktorik::getInstance();
}

CheckDrill::~CheckDrill(){

}

DrillChecked::DrillChecked(){
	hal_aktorik_ = HALAktorik::getInstance();
}

DrillChecked::~DrillChecked(){

}

TooSmall::TooSmall(){
	hal_aktorik_ = HALAktorik::getInstance();

}
TooSmall::~TooSmall(){

}

WaitingHeightM1::~WaitingHeightM1() {
	hal_aktorik_ = HALAktorik::getInstance();
	// TODO Auto-generated destructor stub
}

void WaitingHeightM1::inHeightMeasurement(){
#ifdef DEBUG_
	cout << "WaitingHeightM1::inHeightMeasurement" << endl;
#endif
	new (this) TooSmall;
}

void WaitingHeightM1::inToleranceRange(){
#ifdef DEBUG_
	cout << "WaitingHeightM1->inToleranceRange" << endl;
#endif
	new (this) CheckDrill;
}

void CheckDrill::inHeightMeasurement(){
#ifdef DEBUG_
	cout << "CheckDrill::inHeightMeasurement" << endl;
#endif
	new (this) DrillChecked;
}

void DrillChecked::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "DrillChecked::outHeightMeasurement" << endl;
#endif
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	new (this) WaitingHeightM1;
}

void TooSmall::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "TooSmall::outHeightMeasurement" << endl;
#endif
	new (this) WaitingHeightM1;
}

