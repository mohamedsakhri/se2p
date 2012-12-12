/*
 * @file	SegLineStart.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 1
 *
 */


#include "SegLineStart.h"
//#define DEBUG_


/************************************************************************************
 *									StateLineStart									*
 *																					*
 ************************************************************************************/

StateLineStart::StateLineStart() {
//	hal_aktorik_ = HALAktorik::getInstance();
	cout << "StateLine :: Constructor" << endl;
}

void StateLineStart::inLineStart()
{
#ifdef DEBUG_
	cout << "StateLineStart :: inLineStart" << endl;
#endif
	//TODO check if the WP id is needed
	WorkPiece* wp = new WorkPiece(1) ;
	ControllerSeg1::getInstance()->addWP2List(wp);
	//TODO test if the motor have to be started
	if (ControllerSeg5::getInstance()->isFifoEmpty()){
		HALAktorik::getInstance()->motor_on();
		HALAktorik::getInstance()->green_Light_on();
	}
	new (this) StateWorkPieceCreated();

}

StateLineStart::~StateLineStart() {
}


/************************************************************************************
 *									StateWorkPieceCreated							*
 *																					*
 ************************************************************************************/

StateWorkPieceCreated::StateWorkPieceCreated(){
#ifdef DEBUG_
	cout << "StateWorkPieceCreated :: Constructor" << endl;
#endif
}

void StateWorkPieceCreated::outLineStart(){
#ifdef DEBUG_
	cout << "StateWorkPieceCreated :: outLineStart" << endl;
#endif
	// Start timer ??
	if (!ControllerSeg1::getInstance()->isFifoEmpty()) {
		ControllerSeg1::getInstance()->passWP2Ctr();
		ControllerSeg1::getInstance()->removeFirsttWP();

		new (this) StateLineStart();
	} else {
		//TODO  just send msg and let controller do the rest according to the error event handler
		ControllerSeg1::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->red_Light_on();
		HALAktorik::getInstance()->green_Light_off();
	}
}

StateWorkPieceCreated::~StateWorkPieceCreated(){

}


