/*
 * @file	SegSwitch.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 3
 *
 */

#include "SegSwitch.h"
#define DEBUG_


/************************************************************************************
 *									WaitingSwitch									*
 *																					*
 ************************************************************************************/

WaitingSwitch::WaitingSwitch() {
#ifdef DEBUG_
	cout << "WaitingSwitch Start constructor" << endl;
#endif
}

void WaitingSwitch::inSwitch() {
	if (!ControllerSeg3::getInstance()->isFifoEmpty()) {
		if (ControllerSeg3::getInstance()->getFirstWP()->getIs_inTolleranceRange()) {
			HALAktorik::getInstance()->open_Switch();
			new (this) WorkPieceValid();
		} else {
			new (this) WorkPieceInvalid();
		}
	} else {
		//TODO  just send msg and let controller do the rest according to the error event handler
		ControllerSeg3::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->red_Light_on();
		HALAktorik::getInstance()->green_Light_off();
	}
}

WaitingSwitch::~WaitingSwitch() {
}


/************************************************************************************
 *									WorkPieceInvalid								*
 *																					*
 ************************************************************************************/

WorkPieceInvalid::WorkPieceInvalid()
{
#ifdef DEBUG_
	cout << "WorkPieceInValid Start constructor" << endl;
#endif
}

void WorkPieceInvalid::outSwitch()
{
	ControllerSeg3::getInstance()->passWP2Ctr(CONTROLLER_SEG4);
	ControllerSeg3::getInstance()->removeFirsttWP();
	new (this) WaitingSwitch();
}

WorkPieceInvalid::~WorkPieceInvalid()
{
}


/************************************************************************************
 *									WorkPieceValid									*
 *																					*
 ************************************************************************************/

WorkPieceValid::WorkPieceValid()
{
#ifdef DEBUG_
	cout << "WorkPieceValid Start constructor" << endl;
#endif
}


void WorkPieceValid::outSwitch()
{
#ifdef DEBUG_
	cout << "Switch closed" << endl;
#endif

	ControllerSeg3::getInstance()->passWP2Ctr(CONTROLLER_SEG5);
	ControllerSeg3::getInstance()->removeFirsttWP();
	HALAktorik::getInstance()->close_Switch();
	new (this) WaitingSwitch();
}


WorkPieceValid::~WorkPieceValid()
{
}


