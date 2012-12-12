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


/************************************************************************************
 *									SlideWait										*
 *																					*
 ************************************************************************************/

SlideWait::SlideWait()
{
#ifdef DEBUG_
	cout << "SlideWait Start constructor" << endl;
#endif
}


void SlideWait::inSlide()
{
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

void InSlide::outSlide()
{
	delete ControllerSeg4::getInstance()->getFirstWP();
	ControllerSeg4::getInstance()->removeFirsttWP();
	if (ControllerSeg1::getInstance()->isFifoEmpty()
			&& ControllerSeg2::getInstance()->isFifoEmpty()
			&& ControllerSeg3::getInstance()->isFifoEmpty()
			&& ControllerSeg5::getInstance()->isFifoEmpty())
	{
		HALAktorik::getInstance()->stop_Motor();
	}

	new (this) SlideWait();
}

InSlide::~InSlide()
{
}


#define DEBUG_
