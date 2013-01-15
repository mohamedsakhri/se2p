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

//#define DEBUG_

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
	ControllerSeg4::getInstance()->getFirstWP()->getTimer()->stop();
	ControllerSeg4::getInstance()->getTimer()->setNewTime(TWO_SEC,NULL_MSEC);
	ControllerSeg4::getInstance()->getTimer()->start();
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

	if (ControllerSeg1::getInstance()->isFifoEmpty()
			&& ControllerSeg2::getInstance()->isFifoEmpty()
			&& ControllerSeg3::getInstance()->isFifoEmpty()
			&& ControllerSeg4::getInstance()->isFifoEmpty()
			&& ControllerSeg5::getInstance()->isFifoEmpty()) {

		HALAktorik::getInstance()->motor_off();

	}
	new (this) SlideWait();
}

InSlide::~InSlide()
{
}

#define DEBUG_
