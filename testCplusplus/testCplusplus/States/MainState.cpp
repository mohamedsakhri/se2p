/*
 * @file	MainState.cpp
 *
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 19, 2012
 *
 * Classes which represent the main state
 *
 */


#include "MainState.h"

//#define DEBUG_

/************************************************************************************
 *									initState									*
 *																					*
 ************************************************************************************/

InitState::InitState() {

}

InitState::~InitState() {

}

void InitState::startPressed() {
	HALAktorik::getInstance()->red_Light_off();
	HALAktorik::getInstance()->green_Light_on();
	HALAktorik::getInstance()->yellow_Light_off();
	HALAktorik::getInstance()->Start_LED_on();

	new (this) RunningMachine1();
}

/************************************************************************************
 *									RunningMachine1									*
 *																					*
 ************************************************************************************/
RunningMachine1::RunningMachine1()
{

}

RunningMachine1::~RunningMachine1()
{

}

void RunningMachine1::stopPressed()
{
	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->red_Light_off();
	HALAktorik::getInstance()->green_Light_off();
	HALAktorik::getInstance()->yellow_Light_off();
	HALAktorik::getInstance()->Start_LED_off();

	Dispatcher::getInstance()->removeHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg5::getInstance());

	new (this) Stop();
}

void RunningMachine1::EStopPressed()
{
	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->Start_LED_off();
}

void RunningMachine1::error()
{

}

/************************************************************************************
 *									ErrorHandling									*
 *																					*
 ************************************************************************************/
ErrorHandling::ErrorHandling()
{

}

ErrorHandling::~ErrorHandling()
{

}

void ErrorHandling::errorFixed()
{

}

void ErrorHandling::resetMachine()
{

}

/************************************************************************************
 *									Stop									*
 *																					*
 ************************************************************************************/
Stop::Stop()
{

}

Stop::~Stop()
{

}

void Stop::startPressed()
{
	if (MainController::getInstance()->isRunning()) {
		HALAktorik::getInstance()->motor_on();
	}
	HALAktorik::getInstance()->red_Light_off();
	HALAktorik::getInstance()->green_Light_on();
	HALAktorik::getInstance()->yellow_Light_off();
	HALAktorik::getInstance()->Start_LED_on();

	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());

	new (this) RunningMachine1();
}

void Stop::resetMachine()
{

	new (this) InitState();
}


/************************************************************************************
 *									Emergency									*
 *																					*
 ************************************************************************************/
Emergency::Emergency()
{

}

Emergency::~Emergency()
{

}

//TODO Only Reset is allowed when EStop released
void Emergency::EStopReleased()
{

}
