/*
 * WaitingSwitch.cpp
 *
 *  Created on: 07.12.2012
 *      Author: aax844
 */

#include "WaitingSwitch.h"
#define DEBUG_

//TODO removeWP fehlt
//------------WaitingSwitsch--------------------

WaitingSwitch::WaitingSwitch()
{
#ifdef DEBUG_
	cout << "WaitingSwitch Start constructor" << endl;
#endif
}

WaitingSwitch::~WaitingSwitch()
{
}

void WaitingSwitch::inSwitch()
{
//	WorkPiece wp = ControllerSeg3::getInstance()->getFirstWP();
	if(ControllerSeg3::getInstance()->getFirstWP()->getIs_inTolleranceRange())
	{
		HALAktorik::getInstance()->open_Switch();
		new (this) WorkPieceValid();
	}
	else
	{
		new (this) WorkPieceInvalid();
	}


}

//------------WorkPieceInvalid--------------------

WorkPieceInvalid::WorkPieceInvalid()
{
#ifdef DEBUG_
	cout << "WorkPieceInValid Start constructor" << endl;
#endif
}


WorkPieceInvalid::~WorkPieceInvalid()
{
}

void WorkPieceInvalid::outSwitch()
{
	ControllerSeg3::getInstance()->removeFirsttWP();
	new (this) WaitingSwitch();
}



//------------WorkPiecevalid--------------------

WorkPieceValid::WorkPieceValid()
{
#ifdef DEBUG_
	cout << "WorkPieceValid Start constructor" << endl;
#endif
}


WorkPieceValid::~WorkPieceValid()
{
}

void WorkPieceValid::outSwitch()
{
	cout << "close switch" << endl;
	ControllerSeg3::getInstance()->removeFirsttWP();
	HALAktorik::getInstance()->close_Switch();
	new (this) WaitingSwitch();
}


