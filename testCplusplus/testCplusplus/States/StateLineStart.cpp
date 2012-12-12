/*
 * StateLineStart.cpp
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#include "StateLineStart.h"
#define DEBUG_

StateLineStart::StateLineStart() {
//	hal_aktorik_ = HALAktorik::getInstance();
	cout << "stateLine Start constructur" << endl;
}

StateLineStart::~StateLineStart() {
	// TODO Auto-generated destructor stub
}


void StateLineStart::inLineStart()
{
#ifdef DEBUG_
	cout << "StateLineStart->inLineStart" << endl;
#endif
	//TODO check if the WP id is needed
	WorkPiece* wp = new WorkPiece(1) ;
	ControllerSeg1::getInstance()->addWP2List(wp);
	//TODO test if the motor have to be started
	HALAktorik::getInstance()->motor_on();
	HALAktorik::getInstance()->green_Light_on();
	new (this) StateWorkPieceCreated();
}


//---------------------StateWorkPieceCreated-----------------


StateWorkPieceCreated::StateWorkPieceCreated(){
	cout << "StateWorkPieceCreated Start constructur" << endl;
}

StateWorkPieceCreated::~StateWorkPieceCreated(){

}

void StateWorkPieceCreated::outLineStart(){
	#ifdef DEBUG_
	cout << "StateWorkPieceCreated->outLineStart" << endl;
	#endif
	// Start timer ??
	ControllerSeg1::getInstance()->passWP2Ctr();
	ControllerSeg1::getInstance()->removeLastWP();

	new (this) StateLineStart();
	cout << "StateWorkPieceCreated->outLineStart END" << endl;
}