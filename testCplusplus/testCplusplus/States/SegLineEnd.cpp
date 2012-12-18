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
	cout << "WaitLineEndM1 :: Constructor " << endl;
#endif
}

void WaitLineEndM1::inLineEnd()
{
	if (!ControllerSeg5::getInstance()->isFifoEmpty()) {
		if (ControllerSeg5::getInstance()->getFirstWP()->getHas_Drill()) {
			new (this) TransferMachine2();
		} else {
		//	HALAktorik::getInstance()->yellow_Light_on();
			LightFlash::getInstance()->flash(YELLOW,HALF_S);
			HALAktorik::getInstance()->motor_off();
			HALAktorik::getInstance()->green_Light_off();

			new (this) WaitForTurn();
		}
	} else {
		//TODO  just send msg and let controller do the rest according to the error event_ handler
		ControllerSeg5::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
		//to be moved to ERROR
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->red_Light_on();
		HALAktorik::getInstance()->green_Light_off();
		//HALAktorik::getInstance()->yellow_Light_off();
		LightFlash::getInstance()->stopFlashing();
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
	cout << "WaitForTurn :: Constructor" << endl;
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
	cout << "Turning :: Constructor" << endl;
#endif
}

void Turning::inLineEnd()
{
	HALAktorik::getInstance()->motor_on();
//	HALAktorik::getInstance()->yellow_Light_off();
	LightFlash::getInstance()->stopFlashing();
	HALAktorik::getInstance()->green_Light_on();
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
	cout << "TransferMachine2 :: Constructor" << endl;
#endif
	machine2IsReady();
}

void TransferMachine2::machine2IsReady()
{
	if (ControllerSeg5::getInstance()->isMachin2Ready() ){
		HALAktorik::getInstance()->motor_on();
		new (this) Machine2Ready();
		}
		else {
			HALAktorik::getInstance()->motor_off();
	//		HALAktorik::getInstance()->yellow_Light_on();
	//		HALAktorik::getInstance()->green_Light_off();
			new (this) WaitForMachine2();
		}

}

TransferMachine2::~TransferMachine2()
{
}


/************************************************************************************
 *									WaitForMachine2									*
 *																					*
 ************************************************************************************/

WaitForMachine2::WaitForMachine2()
{
#ifdef DEBUG_
	cout << "WaitForMachine2 :: Constructor" << endl;
#endif
}

void WaitForMachine2::messageReceived()
{
	HALAktorik::getInstance()->motor_on();

	new (this) Machine2Ready();

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
	cout << "Machine2Ready :: Constructor" << endl;
#endif
}

//TODO has to be changed. Just for get things in M! now
void Machine2Ready::outLineEnd()
{
	if (!ControllerSeg5::getInstance()->isFifoEmpty()) {
		ControllerSeg5::getInstance()->passWP2Ctr();
		ControllerSeg5::getInstance()->removeFirsttWP();

		Sender::getInstance()->send(WP_IS_COMMING);
		cout << "WP_IS_COMMING SENT" <<endl;
		new (this) WaitLineEndM1();
	} else {
		HALAktorik::getInstance()->red_Light_on();
		HALAktorik::getInstance()->green_Light_off();
	}
}

Machine2Ready::~Machine2Ready()
{
}

#define DEBUG_
