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
	new (this) SlideWait();
}

InSlide::~InSlide()
{
}


#define DEBUG_
