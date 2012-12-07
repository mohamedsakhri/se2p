/*
 * StateLineStart.cpp
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#include "StateLineStart.h"
#define DEBUG_

StateLineStart::StateLineStart(HALCallInterface* ctr) {
	hal_aktorik_ = HALAktorik::getInstance();
	this->controller = ctr;
}

StateLineStart::~StateLineStart() {
	// TODO Auto-generated destructor stub
}

StateWorkPieceCreated::StateWorkPieceCreated(){
	hal_aktorik_ = HALAktorik::getInstance();
}

StateWorkPieceCreated::~StateWorkPieceCreated(){

}

void StateLineStart::inLineStart()
{
#ifdef DEBUG_
	cout << "StateLineStart->inLineStart" << endl;
#endif
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	new (this) StateWorkPieceCreated;
}
void StateWorkPieceCreated::outLineStart(){
	#ifdef DEBUG_
	cout << "StateWorkPieceCreated->outLineStart" << endl;
	#endif

	new (this) StateLineStart(this->controller);
}
