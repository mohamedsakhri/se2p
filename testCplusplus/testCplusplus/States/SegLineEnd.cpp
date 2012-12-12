/*
 * @file	SegLineEnd.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 5
 *
 */

#include "SegLineEnd.h"

#define DEBUG_


/************************************************************************************
 *									WaitLineEndM1									*
 *																					*
 ************************************************************************************/

WaitLineEndM1::WaitLineEndM1()
{
#ifdef DEBUG_
	cout << "WaitLineEndM1 Start constructor" << endl;
#endif
}

void WaitLineEndM1::inLineEnd()
{
	if (ControllerSeg5::getInstance()->getFirstWP()->getHas_Drill()) {
		new (this) TransferMachine2();
	} else {
		HALAktorik::getInstance()->yellow_Light_on();
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->green_Light_off();

		new (this) WaitForTurn();
	}

}

WaitLineEndM1::~WaitLineEndM1()
{
}

/************************************************************************************
 *									WaitForTurn										*
 *																					*
 ************************************************************************************/

WaitForTurn::WaitForTurn()
{
#ifdef DEBUG_
	cout << "WaitForTurn Start constructor" << endl;
#endif
}

void WaitForTurn::outLineEnd()
{
	new (this) Turning();
}

WaitForTurn::~WaitForTurn()
{
}

/************************************************************************************
 *									Turning											*
 *																					*
 ************************************************************************************/

Turning::Turning()
{
#ifdef DEBUG_
	cout << "Turning Start constructor" << endl;
#endif
}

void Turning::inEndLine()
{
	new (this) TransferMachine2();
}

Turning::~Turning()
{
}

/************************************************************************************
 *									TransferMachine2								*
 *																					*
 ************************************************************************************/

TransferMachine2::TransferMachine2()
{
#ifdef DEBUG_
	cout << "TransferMachine2 Start constructor" << endl;
#endif
}

void TransferMachine2::messageReceived()
{
//TODO  communicate with machine 2
	new (this) Machine2Ready();
}

TransferMachine2::~TransferMachine2()
{
}

/************************************************************************************
 *									Machine2Ready									*
 *																					*
 ************************************************************************************/

WaitForMachine2::WaitForMachine2()
{
#ifdef DEBUG_
	cout << "WaitForMachine2 Start constructor" << endl;
#endif
}

void WaitForMachine2::messageReceived()
{
}

WaitForMachine2::~WaitForMachine2()
{
}

/************************************************************************************
 *									Machine2Ready									*
 *																					*
 ************************************************************************************/

Machine2Ready::Machine2Ready()
{
#ifdef DEBUG_
	cout << "Machine2Ready Start constructor" << endl;
#endif
}

void Machine2Ready::outEndLine()
{
	if (ControllerSeg1::getInstance()->isFifoEmpty()
			&& ControllerSeg2::getInstance()->isFifoEmpty()
			&& ControllerSeg3::getInstance()->isFifoEmpty()
			&& ControllerSeg5::getInstance()->isFifoEmpty())
	{
		HALAktorik::getInstance()->stop_Motor();
	}

}

Machine2Ready::~Machine2Ready()
{
}

#define DEBUG_
