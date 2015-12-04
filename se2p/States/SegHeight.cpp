/*
 * @file	SegHeight.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 2
 *
 */

#include "SegHeight.h"
#define DEBUG_

/************************************************************************************
 *									WaitingHeighM1									*
 *																					*
 ************************************************************************************/

WaitingHeightM1::WaitingHeightM1()
{
#ifdef DEBUG_
	cout << "WaitingHeightM1 :: Constructor" << endl;
#endif
}

WaitingHeightM1::~WaitingHeightM1()
{
}

void WaitingHeightM1::inHeightMeasurement()
{
#ifdef DEBUG_
	cout << "WaitingHeightM1 :: inHeightMeasurement" << endl;
#endif
	// WP has arrived, stop timer and  set new time for Seg3
	ControllerSeg2::getInstance()->getFirstWP()->getTimer()->stop();
//	ControllerSeg2::getInstance()->getFirstWP()->getTimer()->setNewTime(FOUR_SEC,NULL_MSEC);
	ControllerSeg2::getInstance()->getFirstWP()->getTimer()->start(FOUR_SEC,NULL_MSEC);

	new (this) TooSmall();
}

void WaitingHeightM1::inToleranceRange()
{
#ifdef DEBUG_
	cout << "WaitingHeightM1 :: inToleranceRange" << endl;
#endif
	// WP has arrived, stop timer and  set new time for Seg3
	ControllerSeg2::getInstance()->getFirstWP()->getTimer()->stop();
//	ControllerSeg2::getInstance()->getFirstWP()->getTimer()->setNewTime(FOUR_SEC,NULL_MSEC);
	ControllerSeg2::getInstance()->getFirstWP()->getTimer()->start(FOUR_SEC,NULL_MSEC);

	ControllerSeg2::getInstance()->getFirstWP()->setIs_inTolleranceRange(true);
	ControllerSeg2::getInstance()->getFirstWP()->setHas_Drill(false);

	new (this) CheckDrill();
}


/************************************************************************************
 *									TooSmall										*
 *																					*
 ************************************************************************************/

TooSmall::TooSmall()
{
	cout << "TooSmall :: Constructor" << endl;
}

TooSmall::~TooSmall()
{
}

void TooSmall::outHeightMeasurement()
{
#ifdef DEBUG_
	cout << "TooSmall :: outHeightMeasurement" << endl;
#endif
	// Start timer ??
	if (!ControllerSeg2::getInstance()->isFifoEmpty()) {
		ControllerSeg2::getInstance()->passWP2Ctr();
		ControllerSeg2::getInstance()->removeFirsttWP();

//		// WP has arrived, stop timer and  set new time for Seg3
//		ControllerSeg2::getInstance()->getFirstWP()->getTimer()->stop();
//		ControllerSeg2::getInstance()->getFirstWP()->getTimer()->setNewTime(TWO_SEC,NULL_MSEC);
//		ControllerSeg2::getInstance()->getFirstWP()->getTimer()->start();

		new (this) WaitingHeightM1();
	} else {
		//TODO  just send msg and let controller do the rest according to the error event_ handler
		ControllerSeg2::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
	}
}


/************************************************************************************
 *									CheckDrill										*
 *																					*
 ************************************************************************************/

CheckDrill::CheckDrill()
{
	cout << "CheckDrill :: Constructor" << endl;
}

CheckDrill::~CheckDrill()
{

}

void CheckDrill::outHeightMeasurement()
{
#ifdef DEBUG_
	cout << "CheckDrill :: inHeightMeasurement" << endl;
#endif

//		ControllerSeg2::getInstance()->getFirstWP()->setHas_Drill(true);
			if (!ControllerSeg2::getInstance()->isFifoEmpty()) {
#ifdef DEBUG_
				if(ControllerSeg2::getInstance()->getFirstWP()->getHas_Drill()){
					cout << "----------> LOCH : OBEN" << endl;
				}else {
					cout << "----------> LOCH : UNTEN" << endl;
				}
#endif
				// WP has arrived, stop timer and  set new time for Seg3
//				ControllerSeg2::getInstance()->getFirstWP()->getTimer()->stop();
//				ControllerSeg2::getInstance()->getFirstWP()->getTimer()->setNewTime(TWO_SEC,NULL_MSEC);
//				ControllerSeg2::getInstance()->getFirstWP()->getTimer()->start();

				ControllerSeg2::getInstance()->passWP2Ctr();
				ControllerSeg2::getInstance()->removeFirsttWP();

				new (this) WaitingHeightM1();
			} else {
				ControllerSeg2::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
			}
	new (this) WaitingHeightM1();
}

void CheckDrill::inToleranceRange()
{
#ifdef DEBUG_
	cout << "CheckDrill :: notInToleranceRange " << endl;
#endif

	ControllerSeg2::getInstance()->getFirstWP()->setHas_Drill(true);
}
