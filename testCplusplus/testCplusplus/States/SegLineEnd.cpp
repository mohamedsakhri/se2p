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
	// Workpiece has arrived : Stop timer
	ControllerSeg5::getInstance()->getFirstWP()->getTimer()->stop();

	if (!ControllerSeg5::getInstance()->isFifoEmpty()) {
		if (ControllerSeg5::getInstance()->getFirstWP()->getHas_Drill()) {
			new (this) TransferMachine2();
		} else {
		//	HALAktorik::getInstance()->yellow_Light_on();
			MainController::getInstance()->setIsRunning(false);
			HALAktorik::getInstance()->motor_off();
			LightFlash::getInstance()->flash(YELLOW,HALF_S);
			// Pause all timers while motor is stopped
			MainController::getInstance()->pauseAllTimers();

			new (this) WaitForTurn();
		}
	} else {
		//TODO  just send msg and let controller do the rest according to the error event_ handler
		ControllerSeg5::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
		//to be moved to ERROR
		HALAktorik::getInstance()->motor_off();
//		HALAktorik::getInstance()->red_Light_on();
//		HALAktorik::getInstance()->green_Light_off();
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
	ControllerSeg5::getInstance()->getTimer()->start();
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
#ifdef DEBUG_
	cout << "Turning :: Timer stopped" << endl;
#endif
	ControllerSeg5::getInstance()->getTimer()->stop();
	MainController::getInstance()->resumeAllTimers();
	HALAktorik::getInstance()->motor_on();
	MainController::getInstance()->setIsRunning(true);
//	HALAktorik::getInstance()->yellow_Light_off();
	LightFlash::getInstance()->stopFlashing();
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
#ifdef DEBUG_
	cout << "TransferMachine2 :: machine2IsReady" << endl;
#endif
	if (ControllerSeg5::getInstance()->isMachin2Ready() ){
		HALAktorik::getInstance()->motor_on();
		MainController::getInstance()->setIsRunning(true);
		new (this) Machine2Ready();
		}
		else {
			MainController::getInstance()->pauseAllTimers();
			HALAktorik::getInstance()->motor_off();
			MainController::getInstance()->setIsRunning(false);
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
	MainController::getInstance()->resumeAllTimers();

	HALAktorik::getInstance()->motor_on();
	MainController::getInstance()->setIsRunning(true);

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
#ifdef DEBUG_
	cout << "Machine2Ready :: outLineEnd" << endl;
#endif

	if (!ControllerSeg5::getInstance()->isFifoEmpty()) {
		ControllerSeg5::getInstance()->removeFirsttWP();
		// Notify machine 2 that a WP is comming
		Sender::getInstance()->send(WP_IS_COMMING);

		new (this) WaitLineEndM1();

	} else {
		// Case of Error
		ControllerSeg5::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
//		HALAktorik::getInstance()->red_Light_on();
//		HALAktorik::getInstance()->green_Light_off();
	}
}

Machine2Ready::~Machine2Ready()
{
}

#define DEBUG_
