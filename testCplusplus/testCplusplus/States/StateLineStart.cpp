/*
 * StateLineStart.cpp
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#include "StateLineStart.h"
#define DEBUG_

StateLineStart::StateLineStart() {
	hal_aktorik_ = HALAktorik::getInstance();
	this->controller = ctr;
}

StateLineStart::~StateLineStart() {
	// TODO Auto-generated destructor stub
}


void StateLineStart::inLineStart()
{
#ifdef DEBUG_
	cout << "StateLineStart->inLineStart" << endl;
	cout << "StateLineStart : Controller Id = " << ControllerSeg1::getInstance()->getControllerId() << endl;
#endif
	WorkPiece wp(1) ;
	ControllerSeg1::getInstance()->addWP2List(wp);
	//TODO test if the motor have to be started
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	new (this) StateWorkPieceCreated();
}


//---------------------StateWorkPieceCreated-----------------


StateWorkPieceCreated::StateWorkPieceCreated(){
	this->controller = ctr;
	hal_aktorik_ = HALAktorik::getInstance();
}

StateWorkPieceCreated::~StateWorkPieceCreated(){

}

void StateWorkPieceCreated::outLineStart(){
	#ifdef DEBUG_
	cout << "StateWorkPieceCreated->outLineStart" << endl;
	#endif
	// Start timer ??

	ControllerSeg1::getInstance()->removeLastWP();
	new (this) StateLineStart();
}
