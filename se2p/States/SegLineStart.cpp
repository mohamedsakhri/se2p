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
#define DEBUG_


/************************************************************************************
 *									StateLineStart									*
 *																					*
 ************************************************************************************/
/**
 *
 */
StateLineStart::StateLineStart()
{
#ifdef DEBUG_
	cout << "StateLineStart :: Constructor" << endl;
#endif
}

void StateLineStart::inLineStart()
{
#ifdef DEBUG_
	cout << "StateLineStart :: inLineStart" << endl;
#endif
	MainController::getInstance()->setIsRunning(true);

	WorkPiece* wp = new WorkPiece() ;
	ControllerSeg1::getInstance()->addWP2List(wp);

	if (ControllerSeg5::getInstance()->isFifoEmpty()){
		HALAktorik::getInstance()->motor_on();
		HALAktorik::getInstance()->green_Light_on();
	}
	new (this) StateWorkPieceCreated();

}

/**
 *
 */
StateLineStart::~StateLineStart()
{
}

/************************************************************************************
 *									StateWorkPieceCreated							*
 *																					*
 ************************************************************************************/

StateWorkPieceCreated::StateWorkPieceCreated()
{
#ifdef DEBUG_
	cout << "StateWorkPieceCreated :: Constructor" << endl;
#endif
}

void StateWorkPieceCreated::outLineStart()
{
#ifdef DEBUG_
	cout << "StateWorkPieceCreated :: outLineStart" << endl;
#endif
	if (!ControllerSeg1::getInstance()->isFifoEmpty()) {
		// Start timer for seg2
//		ControllerSeg1::getInstance()->getFirstWP()->getTimer()->setNewTime(THREE_SEC, NULL_MSEC);
		ControllerSeg1::getInstance()->getFirstWP()->getTimer()->start(THREE_SEC, NULL_MSEC);

		ControllerSeg1::getInstance()->passWP2Ctr();
		ControllerSeg1::getInstance()->removeFirsttWP();

		new (this) StateLineStart();
	} else {
		ControllerSeg1::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
	}
}

/**
 *
 */
StateWorkPieceCreated::~StateWorkPieceCreated()
{

}


