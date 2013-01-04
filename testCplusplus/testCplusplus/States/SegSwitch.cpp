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
//#define DEBUG_


/************************************************************************************
 *									WaitingSwitch									*
 *																					*
 ************************************************************************************/

WaitingSwitch::WaitingSwitch() {
#ifdef DEBUG_
	cout << "WaitingSwitch :: Constructor" << endl;
#endif
}


/*
 *
 * Check if WP is stranger  first //TODO May be in Error handling
 */
void WaitingSwitch::inSwitch()
{
	if (!ControllerSeg3::getInstance()->isFifoEmpty()) {
		ControllerSeg3::getInstance()->getFirstWP()->getTimer()->stop();
		if (ControllerSeg3::getInstance()->getFirstWP()->getIs_inTolleranceRange()) {
			// WP has arrived, stop timer and  set new time for Seg5
			ControllerSeg3::getInstance()->getFirstWP()->getTimer()->setNewTime(7,0);
			ControllerSeg3::getInstance()->getFirstWP()->getTimer()->start();

			HALAktorik::getInstance()->open_Switch();
			new (this) WorkPieceValid();
		} else {
			ControllerSeg3::getInstance()->getFirstWP()->getTimer()->setNewTime(4,0);
			ControllerSeg3::getInstance()->getFirstWP()->getTimer()->start();
			new (this) WorkPieceInvalid();
		}
	} else {
		//TODO  just send msg and let controller do the rest according to the error event_ handler
		ControllerSeg3::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->red_Light_on();
		HALAktorik::getInstance()->green_Light_off();
	}
}

WaitingSwitch::~WaitingSwitch()
{
}


/************************************************************************************
 *									WorkPieceInvalid								*
 *																					*
 ************************************************************************************/

WorkPieceInvalid::WorkPieceInvalid()
{
#ifdef DEBUG_
	cout << "WorkPieceInValid :: Constructor" << endl;
#endif
}

/**
 *
 */
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
	cout << "WorkPieceValid :: Constructor" << endl;
#endif
}

void WorkPieceValid::outSwitch()
{
	//Set new time for Segment 5 - From Switch to line  end -
	ControllerSeg3::getInstance()->getFirstWP()->getTimer()->setNewTime(6, 0);
	ControllerSeg3::getInstance()->getFirstWP()->getTimer()->start();
	ControllerSeg3::getInstance()->passWP2Ctr(CONTROLLER_SEG5);
	ControllerSeg3::getInstance()->removeFirsttWP();
	new (this) WaitingSwitch();
	// Use this to wait a bit before closing switching. Just for now!
//	WAIT_HALF_S;
	HALAktorik::getInstance()->close_Switch();

}

WorkPieceValid::~WorkPieceValid()
{
}
