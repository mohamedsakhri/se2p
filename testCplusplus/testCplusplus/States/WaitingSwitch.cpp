/*
 * WaitingSwitch.cpp
 *
 *  Created on: 07.12.2012
 *      Author: aax844
 */

#include "WaitingSwitch.h"

//TODO removeWP fehlt
//------------WaitingSwitsch--------------------

WaitingSwitch::WaitingSwitch(HALCallInterface *ctr)
{
	hal_aktorik_ = HALAktorik::getInstance();
	this->controller = ctr;
}

WaitingSwitch::~WaitingSwitch()
{
}

void WaitingSwitch::inSwitch()
{
	//TODO WorkPiece wp = controller.getOldWP() ;
	WorkPiece wp = controller->getLastWP();
	if(wp.getIs_inTolleranceRange())
	{
		hal_aktorik_->open_Switch();
		new (this) WorkPieceValid(controller);
	}
	else
	{
		new (this) WorkPieceInvalid(controller);
	}


}

//------------WorkPieceInvalid--------------------

WorkPieceInvalid::WorkPieceInvalid(HALCallInterface *ctr)
{
	hal_aktorik_ = HALAktorik::getInstance();
	this->controller = ctr;
}


WorkPieceInvalid::~WorkPieceInvalid()
{
}

void WorkPieceInvalid::outSwitch()
{
	new (this) WaitingSwitch(controller);
}



//------------WorkPiecevalid--------------------

WorkPieceValid::WorkPieceValid(HALCallInterface *ctr)
{
	hal_aktorik_ = HALAktorik::getInstance();
	this->controller = ctr;
}


WorkPieceValid::~WorkPieceValid()
{
}

void WorkPieceValid::outSwitch()
{
	hal_aktorik_->close_Switch();
	new (this) WaitingSwitch(controller);
}




















