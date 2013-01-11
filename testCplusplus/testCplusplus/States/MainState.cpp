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

/************************************************************************************
 * initState *
 * *
 ************************************************************************************/

InitState::InitState() {
#ifdef DEBUG_
	cout << "InitState :: Constructor" << endl;
#endif
}

InitState::~InitState() {

}

void InitState::startPressed() {
#ifdef MACHINE_1
	ControllerSeg1 *ctr1 = ControllerSeg1::getInstance();
	ControllerSeg2 *ctr2 = ControllerSeg2::getInstance();
	ControllerSeg3 *ctr3 = ControllerSeg3::getInstance();
	ControllerSeg4 *ctr4 = ControllerSeg4::getInstance();
	ControllerSeg5 *ctr5 = ControllerSeg5::getInstance();

	// Controllers add some events to register to
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
	ctrM2->addEvent(WP_OUT_SLIDE);
	ctrM2->addEvent(WP_OUT_ENGINE_END);

	Dispatcher::getInstance()->registerHandler(ControllerSegM2::getInstance());

	HALAktorik::getInstance()->green_Light_on();
	HALAktorik::getInstance()->Start_LED_on();

#endif

	new (this) RunningMachine1();
}

/************************************************************************************
 * RunningMachine1 *
 * *
 ************************************************************************************/
RunningMachine1::RunningMachine1() {
#ifdef DEBUG_
	cout << "RunningMachine1 :: Constructor" << endl;
#endif
}

RunningMachine1::~RunningMachine1() {

}

void RunningMachine1::resetPressed() {
	RedLightFlash::getInstance()->hold();
	HALAktorik::getInstance()->red_Light_off();
}

void RunningMachine1::stopPressed() {
	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->red_Light_off();
	HALAktorik::getInstance()->green_Light_off();
	HALAktorik::getInstance()->yellow_Light_off();
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
#endif

	new (this) Stop();
}

void RunningMachine1::EStopPressed() {
	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->Start_LED_off();
}

void RunningMachine1::error() {
	new (this) ErrorHandling();

}

void RunningMachine1::slideFull() {
	new (this) SlideHandling();
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
	Dispatcher::getInstance()->removeHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg5::getInstance());

	HALAktorik::getInstance()->motor_off();

	RedLightFlash::getInstance()->flash(RED,HALF_S);

	//TODO send message to M2

}

ErrorHandling::~ErrorHandling() {

}

void ErrorHandling::startPressed() {
#ifdef DEBUG_
	cout << "ErrorHandling :: Constructor" << endl;
#endif

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

	new (this) RunningMachine1;
}

/**
 *
 */
void ErrorHandling::resetPressed() {
#ifdef DEBUG_
	cout << "ErrorHandling :: resetReleased" << endl;
#endif
	//TODO reset every segment to init state
	RedLightFlash::getInstance()->hold();
	HALAktorik::getInstance()->red_Light_on();
}

/*************************************************
 *
 *
 */

/************************************************************************************
 * ErrorHandling *
 * *
 ************************************************************************************/
SlideHandling::SlideHandling() {
#ifdef DEBUG_
	cout << "SlideHandling :: Constructor" << endl;
#endif
	MainController::getInstance()->pauseAllTimers();
	Dispatcher::getInstance()->removeHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg3::getInstance());
//	Dispatcher::getInstance()->removeHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg5::getInstance());

	HALAktorik::getInstance()->motor_off();
	RedLightFlash::getInstance()->flash(RED,HALF_S);


	//TODO send message to M2

}

SlideHandling::~SlideHandling() {

}

void SlideHandling::errorFixed() {
#ifdef DEBUG_
	cout << "ErrorHandling :: Constructor" << endl;
#endif
	MainController::getInstance()->resumeAllTimers();
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
//	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());

	if (!ControllerSeg1::getInstance()->isFifoEmpty()
			|| !ControllerSeg2::getInstance()->isFifoEmpty()
			|| !ControllerSeg3::getInstance()->isFifoEmpty()
			|| !ControllerSeg5::getInstance()->isFifoEmpty()
			) {
		if (MainController::getInstance()->isRunning())
			HALAktorik::getInstance()->motor_on();
	}
	RedLightFlash::getInstance()->flash(RED,ONE_S);

	new (this) RunningMachine1();

}
void SlideHandling::resetPressed() {
#ifdef DEBUG_
	cout << "SlideHandling :: resetReleased" << endl;
#endif
	//TODO reset every segment to init state


	RedLightFlash::getInstance()->hold();
	HALAktorik::getInstance()->red_Light_on();
}

/************************************************************************************
 * Stop *
 * *
 ************************************************************************************/
Stop::Stop() {
#ifdef DEBUG_
	cout << "Stop :: Constructor" << endl;
#endif

}

Stop::~Stop() {

}

void Stop::startPressed() {
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

void Stop::resetMachine() {

	new (this) InitState();
}

/************************************************************************************
 * Emergency *
 * *
 ************************************************************************************/
Emergency::Emergency() {
#ifdef DEBUG_
	cout << "Emergency :: Constructor" << endl;
#endif
}

Emergency::~Emergency() {

}

//TODO Only Reset is allowed when EStop released
void Emergency::EStopReleased() {

}
