/*
 * @file MainState.cpp
 *
 * @author Mohamed Sakhri
 *
 * @date Dec 19, 2012
 *
 * Classes which represent the main state
 *
 */

#include "MainState.h"

#define DEBUG_
#define MACHINE_1
//#define MACHINE_2

/************************************************************************************
  	  	  	  	  	  	  	  	  initState

 ************************************************************************************/

InitState::InitState() {
#ifdef DEBUG_
	cout << "InitState :: Constructor" << endl;
#endif
}

/**
 * Init machine when start button has been pressed
 */
void InitState::startPressed() {
#ifdef MACHINE_1

	// Create controllers for every segment
	ControllerSeg1 *ctr1 = ControllerSeg1::getInstance();
	ControllerSeg2 *ctr2 = ControllerSeg2::getInstance();
	ControllerSeg3 *ctr3 = ControllerSeg3::getInstance();
	ControllerSeg4 *ctr4 = ControllerSeg4::getInstance();
	ControllerSeg5 *ctr5 = ControllerSeg5::getInstance();

	//Controllers add events they want to register to
	ctr1->addEvent(WP_IN_ENGINE_START);
	ctr1->addEvent(WP_OUT_ENGINE_START);

	ctr2->addEvent(WP_IN_HEIGHT_M);
	ctr2->addEvent(WP_OUT_HEIGHT_M);
	ctr2->addEvent(WP_IN_TOLERANCE_R);
	ctr2->addEvent(WP_NOT_IN_TOLERANCE_R);

	ctr3->addEvent(WP_IN_SWITCH);
	ctr3->addEvent(WP_OUT_SWITCH);

	ctr4->addEvent(WP_IN_SLIDE);
	ctr4->addEvent(WP_OUT_SLIDE);

	ctr5->addEvent(WP_IN_ENGINE_END);
	ctr5->addEvent(WP_OUT_ENGINE_END);
	ctr5->addEvent(WP_HAS_ARRIVED);
	ctr5->addEvent(MACHINE2_IS_BUSY);
	ctr5->addEvent(MACHINE2_IS_READY);

	// Register controllers by dispatcher
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());

	HALAktorik::getInstance()->green_Light_on();
	HALAktorik::getInstance()->Start_LED_on();
#endif
#ifdef MACHINE_2

	ControllerSegM2 *ctrM2 = ControllerSegM2::getInstance();

	ctrM2->addEvent(WP_IS_COMMING);
	ctrM2->addEvent(WP_IN_ENGINE_START);
	ctrM2->addEvent(WP_IN_HEIGHT_M);
	ctrM2->addEvent(WP_OUT_HEIGHT_M);
	ctrM2->addEvent(WP_IN_TOLERANCE_R);
	ctrM2->addEvent(WP_IS_METAL);
	ctrM2->addEvent(WP_IN_SWITCH);
	ctrM2->addEvent(WP_OUT_SWITCH);
	ctrM2->addEvent(WP_IN_SLIDE);
	ctrM2->addEvent(WP_OUT_SLIDE);
	ctrM2->addEvent(WP_OUT_ENGINE_END);

	Dispatcher::getInstance()->registerHandler(ControllerSegM2::getInstance());

	HALAktorik::getInstance()->green_Light_on();
	HALAktorik::getInstance()->Start_LED_on();

#endif

	new (this) RunningMachine1();
}

/**
 * Deconstructor has nothing to do
 */
InitState::~InitState() {
#ifdef DEBUG_
	cout << "InitState :: Deconstructor" << endl;
#endif
}

/************************************************************************************
  	  	  	  	  	  RunningMachine1

 ************************************************************************************/
/**
 * Constructor
 */
RunningMachine1::RunningMachine1() {
#ifdef DEBUG_
	cout << "RunningMachine1 :: Constructor" << endl;
#endif
}

/**
 * Error registered : stop flashing or turn red light off
 */
void RunningMachine1::resetPressed() {
	RedLightFlash::getInstance()->hold();
	HALAktorik::getInstance()->red_Light_off();
	HALAktorik::getInstance()->Reset_LED_on();
}

/**
 * Stop button pressed : Turn all lights off and unregister all controllers
 */
//TODO Stop = pause machine or reset everything !
void RunningMachine1::stopPressed() {
	// Stop all timers
	MainController::getInstance()->pauseAllTimers();

	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->Start_LED_off();

#ifdef MACHINE_1
	Dispatcher::getInstance()->removeHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg5::getInstance());
#endif
#ifdef MACHINE_2
	Dispatcher::getInstance()->removeHandler(ControllerSegM2::getInstance());
	Sender::getInstance()->send(MACHINE2_IS_BUSY);
#endif

	new (this) Stop();
}

/**
 * E-Stop button pressed : pause both machines
 */
void RunningMachine1::EStopPressed() {
	HALAktorik::getInstance()->motor_off();
	MainController::getInstance()->pauseAllTimers();

	new (this) Emergency();
	// Send message to stop the other machine
	Sender::getInstance()->send(E_STOP_PRESSED);
}

/**
 *
 */
void RunningMachine1::timeOutError() {
	new (this) ErrorHandling();

}

void RunningMachine1::slideFull() {
	new (this) SlideHandling();
}

/**
 * Deconstructor
 */
RunningMachine1::~RunningMachine1() {
#ifdef DEBUG_
	cout << "RunningMachine1 :: Deconstructor" << endl;
#endif
}

/************************************************************************************
 * ErrorHandling *
 * *
 ************************************************************************************/
ErrorHandling::ErrorHandling() {
#ifdef DEBUG_
	cout << "ErrorHandling :: Constructor" << endl;
#endif
	//TODO stop all timers
	MainController::getInstance()->pauseAllTimers();
#ifdef MACHINE_1
	Dispatcher::getInstance()->removeHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg5::getInstance());
#endif
#ifdef MACHINE_2
	Dispatcher::getInstance()->removeHandler(ControllerSegM2::getInstance());
#endif

	HALAktorik::getInstance()->motor_off();

	RedLightFlash::getInstance()->flash(RED,HALF_S);
}

/**
 *
 */
void ErrorHandling::startPressed() {
#ifdef DEBUG_
	cout << "ErrorHandling :: Constructor" << endl;
#endif
#ifdef MACHINE_1
	ControllerSeg1::getInstance()->reset();
	ControllerSeg2::getInstance()->reset();
	ControllerSeg3::getInstance()->reset();
	ControllerSeg4::getInstance()->reset();
	ControllerSeg5::getInstance()->reset();

	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());
	HALAktorik::getInstance()->red_Light_off();
#endif
#ifdef MACHINE_2
	ControllerSegM2::getInstance()->reset();
	Dispatcher::getInstance()->registerHandler(ControllerSegM2::getInstance());
	Sender::getInstance()->send(MACHINE2_IS_READY);
#endif

	HALAktorik::getInstance()->Start_LED_on();
	new (this) RunningMachine1;
}

/**
 *
 */
void ErrorHandling::resetPressed() {
#ifdef DEBUG_
	cout << "ErrorHandling :: resetReleased" << endl;
#endif
	RedLightFlash::getInstance()->hold();
	HALAktorik::getInstance()->red_Light_on();
	HALAktorik::getInstance()->Reset_LED_on();
}

/**
 *
 */
ErrorHandling::~ErrorHandling() {

}


/************************************************************************************
 	 	 	 	 	 	 	 SlideHandling

 ************************************************************************************/
/**
 *
 */
SlideHandling::SlideHandling() {
#ifdef DEBUG_
	cout << "SlideHandling :: Constructor" << endl;
#endif
	MainController::getInstance()->pauseAllTimers();
#ifdef MACHINE_1
	Dispatcher::getInstance()->removeHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg3::getInstance());
//	Dispatcher::getInstance()->removeHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg5::getInstance());
#endif
#ifdef MACHINE_2
	Dispatcher::getInstance()->removeHandler(ControllerSegM2::getInstance());
#endif

	HALAktorik::getInstance()->motor_off();
	RedLightFlash::getInstance()->flash(RED,HALF_S);
}

/**
 *
 */
void SlideHandling::slideErrorFixed() {
#ifdef DEBUG_
	cout << "ErrorHandling :: Constructor" << endl;
#endif
#ifdef MACHINE_1
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());

	if (!ControllerSeg1::getInstance()->isFifoEmpty()
			|| !ControllerSeg2::getInstance()->isFifoEmpty()
			|| !ControllerSeg3::getInstance()->isFifoEmpty()
			|| !ControllerSeg5::getInstance()->isFifoEmpty()
			) {
		if (MainController::getInstance()->isRunning())
			HALAktorik::getInstance()->motor_on();
	}
#endif
#ifdef MACHINE_2
	Dispatcher::getInstance()->registerHandler(ControllerSegM2::getInstance());
	Sender::getInstance()->send(MACHINE2_IS_READY);
#endif

	RedLightFlash::getInstance()->flash(RED,ONE_S);
	MainController::getInstance()->resumeAllTimers();

	new (this) RunningMachine1();

}

/**
 *
 */
void SlideHandling::resetPressed() {
#ifdef DEBUG_
	cout << "SlideHandling :: resetReleased" << endl;
#endif

	RedLightFlash::getInstance()->hold();
	HALAktorik::getInstance()->red_Light_on();
	HALAktorik::getInstance()->Reset_LED_on();
}

/**
 *
 */
SlideHandling::~SlideHandling() {

}

/************************************************************************************
 	 	 	 	 	 	 	 	 Stop

 ************************************************************************************/
/**
 *
 */
Stop::Stop() {
#ifdef DEBUG_
	cout << "Stop :: Constructor" << endl;
#endif

}

/**
 *
 */
void Stop::startPressed() {
	if (MainController::getInstance()->isRunning()) {
		HALAktorik::getInstance()->motor_on();
		MainController::getInstance()->resumeAllTimers();
	}

	HALAktorik::getInstance()->Start_LED_on();
#ifdef MACHINE_1
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());
#endif
#ifdef MACHINE_2
	Dispatcher::getInstance()->registerHandler(ControllerSegM2::getInstance());
#endif
	new (this) RunningMachine1();
}

/**
 *
 */
Stop::~Stop() {

}

/************************************************************************************
 	 	 	 	 	 	 	 Emergency

 ************************************************************************************/
/**
 * State when E-Stop has been pressed
 */
Emergency::Emergency() {
#ifdef DEBUG_
	cout << "Emergency :: Constructor" << endl;
#endif
}

/**
 *
 */
void Emergency::EStopReleased() {
	new (this) WaitingForReset();
}

/**
 *
 */
Emergency::~Emergency() {

}

/************************************************************************************
 	 	 	 	 	 	 	 WaitingForReset

 ************************************************************************************/
/**
 * State when Reset has been pressed after E-Stop
 */
WaitingForReset::WaitingForReset() {
#ifdef DEBUG_
	cout << "WaitingForReset :: Constructor" << endl;
#endif
}

//TODO Only Reset is allowed when EStop released
/**
 *
 */
void WaitingForReset::ResetPressed() {
	if (MainController::getInstance()->isRunning()) {
		HALAktorik::getInstance()->motor_on();
		MainController::getInstance()->resumeAllTimers();
	}

	HALAktorik::getInstance()->Start_LED_on();
	HALAktorik::getInstance()->Reset_LED_on();

#ifdef MACHINE_1
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());
#endif
#ifdef MACHINE_2
	Dispatcher::getInstance()->registerHandler(ControllerSegM2::getInstance());
#endif
	new (this) RunningMachine1();
}

/**
 *
 */
WaitingForReset::~WaitingForReset() {

}
