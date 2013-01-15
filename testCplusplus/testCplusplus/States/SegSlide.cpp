/*
 * @file	SegSlide.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 4
 *
 */

#include "SegSlide.h"

#define DEBUG_
//#define MACHINE_1
#define MACHINE_2

/************************************************************************************
 *									SlideWait										*
 *																					*
 ************************************************************************************/

SlideWait::SlideWait()
{
#ifdef DEBUG_
	cout << "SlideWait :: Constructor" << endl;
#endif
}


void SlideWait::inSlide()
{
#ifdef MACHINE_1
	ControllerSeg3::getInstance()->passWP2Ctr(CONTROLLER_SEG4);
	ControllerSeg3::getInstance()->removeFirsttWP();
#endif

#ifdef MACHINE_2
	ControllerSegM2::getInstance()->passWP2Ctr();
	ControllerSegM2::getInstance()->removeFirsttWP();
#endif
	ControllerSeg4::getInstance()->getFirstWP()->getTimer()->stop();
//	ControllerSeg4::getInstance()->getTimer()->setNewTime(TWO_SEC,NULL_MSEC);
	ControllerSeg4::getInstance()->getTimer()->start(TWO_SEC,NULL_MSEC);
	new (this) InSlide();
}


SlideWait::~SlideWait()
{
}


/************************************************************************************
 *									InSlide											*
 *																					*
 ************************************************************************************/

InSlide::InSlide()
{
#ifdef DEBUG_
	cout << "InSlide Start constructor" << endl;
#endif
}

/*
 * Free memory located by WP
 * Stop machine if it's empty
 */
void InSlide::outSlide()
{

	ControllerSeg4::getInstance()->getTimer()->stop();
	delete ControllerSeg4::getInstance()->getFirstWP();
	ControllerSeg4::getInstance()->removeFirsttWP();
#ifdef MACHINE_1
	if (ControllerSeg1::getInstance()->isFifoEmpty()
			&& ControllerSeg2::getInstance()->isFifoEmpty()
			&& ControllerSeg3::getInstance()->isFifoEmpty()
			&& ControllerSeg4::getInstance()->isFifoEmpty()
			&& ControllerSeg5::getInstance()->isFifoEmpty()) {

		HALAktorik::getInstance()->motor_off();

	}
	ControllerSeg4::getInstance()->sendMsg2Dispatcher(SLIDE_EMPTY);

#endif
#ifdef MACHINE_2
	if (ControllerSegM2::getInstance()->isFifoEmpty())
		HALAktorik::getInstance()->motor_off();
	ControllerSeg4::getInstance()->sendMsg2Dispatcher(SLIDE_EMPTY);
	Sender::getInstance()->send(MACHINE2_IS_READY);
#endif
	new (this) SlideWait();

}

InSlide::~InSlide()
{
}

#define DEBUG_
