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

#define MACHINE_1		// If programm is running on machine 1.
//#define MACHINE_2		// If programm is running on machine 2.


/************************************************************************************
  	  	  	  	  	  	  	  	  initState

 ************************************************************************************/

/**
 * Constructor has nothing to do.
 */
InitState::InitState() {
#ifdef DEBUG_
	cout << "InitState :: Constructor" << endl;
#endif
}

/**
 * Initialize machine when start button has been pressed the first time.
 */
void InitState::startPressed() {
#ifdef MACHINE_1
	//Create controllers for every segment.
	ControllerSeg1 *ctr1 = ControllerSeg1::getInstance();
	ControllerSeg2 *ctr2 = ControllerSeg2::getInstance();
	ControllerSeg3 *ctr3 = ControllerSeg3::getInstance();
	ControllerSeg4 *ctr4 = ControllerSeg4::getInstance();
	ControllerSeg5 *ctr5 = ControllerSeg5::getInstance();

	//Controllers add events they want to register to.
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

	//Register controllers by dispatcher.
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());

#endif

#ifdef MACHINE_2

	//Create controllers for every segment.
	ControllerSegM2 *ctrM2 = ControllerSegM2::getInstance();
	ControllerSeg4 *ctr4 = ControllerSeg4::getInstance();

	//Controllers add events they want to register to.
	ctrM2->addEvent(WP_IS_COMMING);
	ctrM2->addEvent(WP_IN_ENGINE_START);
	ctrM2->addEvent(WP_IN_HEIGHT_M);
	ctrM2->addEvent(WP_OUT_HEIGHT_M);
	ctrM2->addEvent(WP_IN_TOLERANCE_R);
	ctrM2->addEvent(WP_IS_METAL);
	ctrM2->addEvent(WP_IN_SWITCH);
	ctrM2->addEvent(WP_OUT_SWITCH);
	ctrM2->addEvent(WP_OUT_ENGINE_END);

	ctr4->addEvent(WP_IN_SLIDE);
	ctr4->addEvent(WP_OUT_SLIDE);

	//Register controllers by dispatcher
	Dispatcher::getInstance()->registerHandler(ControllerSegM2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
#endif

	//Green light and Start LED go on.
	HALAktorik::getInstance()->green_Light_on();
	HALAktorik::getInstance()->Start_LED_on();

	//Machine goes to running state.
	new (this) RunningMachine();
}

/**
 * Deconstructor has nothing to do.
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
 * Constructor has nothing to do.
 */
RunningMachine::RunningMachine() {
#ifdef DEBUG_
	cout << "RunningMachine1 :: Constructor" << endl;
#endif
}

/**
 * Error registered : stop flashing or turn red light off.
 */
void RunningMachine::resetPressed() {
	RedLightFlash::getInstance()->stopFlashing();
	HALAktorik::getInstance()->red_Light_off();
	HALAktorik::getInstance()->Reset_LED_on();
	//set error status
	MainController::getInstance()->setErrorRegistered(true);
}

/**
 * Stop button pressed : pause all timers and unregister all controllers.
 * When Stop button is pressed the machine stays as it was.
 */
void RunningMachine::stopPressed() {
	//Pause all timers
	MainController::getInstance()->pauseAllTimers();

	//Turn motor and Start LED off.
	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->Start_LED_off();

	//Unregister all segments' controllers.
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

	//Machine goes to state Stop.
	new (this) Stop();
}

/**
 * E-Stop button pressed : pause both machines.
 */
void RunningMachine::EStopPressed() {
	//Turn motor off.
	HALAktorik::getInstance()->motor_off();
	//Reset LED goes off because it has to be pressed recover machine
	HALAktorik::getInstance()->Reset_LED_off();
	//Pause all timers.
	MainController::getInstance()->pauseAllTimers();
	//Unregister all segments' controllers.

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

	//Machine goes to Emergency state.
	new (this) Emergency();
}

/**
 * When an error related to timer occurred the machine goes to the state that handles timer's errors.
 */
void RunningMachine::timeOutError() {
	new (this) ErrorHandling();

}

/**
 * When the slide becomes full the machine goes to the state that handles slide's errors.
 */
void RunningMachine::slideFull() {
	new (this) SlideHandling();
}

/**
 * When the when a Workpiece is not put back in line when it has to be turned in the end of machine1.
 */
void RunningMachine::turningErrorHandling() {
	new (this) TurningErrorHandling();
}

/**
 * Deconstructor has nothing to do.
 */
RunningMachine::~RunningMachine() {
#ifdef DEBUG_
	cout << "RunningMachine1 :: Deconstructor" << endl;
#endif
}

/************************************************************************************
  	  	  	  	  	  	  	  ErrorHandling

 ************************************************************************************/
/**
 * Constructor stops machine and all timers and unregister all segments' controllers.
 * Red light starts flashing quickly.
 */
ErrorHandling::ErrorHandling() {
#ifdef DEBUG_
	cout << "ErrorHandling :: Constructor" << endl;
#endif

	//Stop all timers.
	MainController::getInstance()->stopAllTimers();

	//Unregister all segment's controllers.
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

	//Stop motor.
	HALAktorik::getInstance()->motor_off();
	//Reset LED goes off because it has to be pressed to register error
	HALAktorik::getInstance()->Reset_LED_off();
	//Start LED goes off. It has to be pressed to start machine again.
	HALAktorik::getInstance()->Start_LED_off();
	//The error has not been registered. Red light start flashing quickly.
	RedLightFlash::getInstance()->flash(RED,HALF_S);
	//set error status
	MainController::getInstance()->setErrorRegistered(false);
}

/**
 * When Start is pressed after an error related to timer, reset all segments' controllers
 * and register them by dispatcher again.
 */
void ErrorHandling::startPressed() {
#ifdef DEBUG_
	cout << "ErrorHandling :: startPressed" << endl;
#endif

	//Reset all segments' controllers.
#ifdef MACHINE_1
	ControllerSeg1::getInstance()->reset();
	ControllerSeg2::getInstance()->reset();
	ControllerSeg3::getInstance()->reset();
	ControllerSeg4::getInstance()->reset();
	ControllerSeg5::getInstance()->reset();

	//Register controllers by dispatcher.
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());
#endif
#ifdef MACHINE_2
	//Reset all segments' controllers.
	ControllerSegM2::getInstance()->reset();
	ControllerSeg4::getInstance()->reset();

	//Register controllers by dispatcher.
	Dispatcher::getInstance()->registerHandler(ControllerSegM2::getInstance());

	//Notify machine1 that machine2 has become ready.
	Sender::getInstance()->send(MACHINE2_IS_READY);
#endif

//	//Turn red light of in case error has been registered.
//	HALAktorik::getInstance()->red_Light_off();
	//Start LED goes on.
	HALAktorik::getInstance()->Start_LED_on();
	if (!MainController::getInstance()->isErrorRegistered()) {
		//Error has been fixed, but not registered yet : red light flashes slowly.
		RedLightFlash::getInstance()->flash(RED,ONE_S);
	}else {
		HALAktorik::getInstance()->red_Light_off();
	}


	//Machine goes back to state running.
	new (this) RunningMachine;
}

/**
 * Register error when it is not yet fixed.
 */
void ErrorHandling::resetPressed() {
#ifdef DEBUG_
	cout << "ErrorHandling :: resetPressed" << endl;
#endif

	//Stop red light flashing
	RedLightFlash::getInstance()->stopFlashing();
	//Red light goes on.
	HALAktorik::getInstance()->red_Light_on();
	//Reset LED goes on.
	HALAktorik::getInstance()->Reset_LED_on();
	//Set error status to registered
	MainController::getInstance()->setErrorRegistered(true);
}

/**
 * Deconstructor has nothing to do.
 */
ErrorHandling::~ErrorHandling() {

}


/************************************************************************************
 	 	 	 	 	 	 	 SlideHandling

 ************************************************************************************/

/**
 * Constructor pauses machine and all timers and unregister all segments' controllers.
 * Slide's controller stays registered to notify the main controller when the slide becomes empty.
 * Red light starts flashing quickly.
 */
SlideHandling::SlideHandling() {
#ifdef DEBUG_
	cout << "SlideHandling :: Constructor" << endl;
#endif
	//Pause all timers.
	MainController::getInstance()->pauseAllTimers();
	//Stop motor.
	HALAktorik::getInstance()->motor_off();
	//Red light starts flashing quickly.
	RedLightFlash::getInstance()->flash(RED,HALF_S);
	//Reset LED goes off because it has to be pressed to register error
	HALAktorik::getInstance()->Reset_LED_off();
	// set error status
	MainController::getInstance()->setErrorRegistered(false);

	//Unregister all segments' controllers but slide's controller.
#ifdef MACHINE_1
	Dispatcher::getInstance()->removeHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg5::getInstance());
#endif
#ifdef MACHINE_2
	Dispatcher::getInstance()->removeHandler(ControllerSegM2::getInstance());
#endif
}

/**
 * Register all segments' controllers again and recover the machine's state.
 *
 */
void SlideHandling::slideErrorFixed() {
#ifdef DEBUG_
	cout << "SlideHandling::slideErrorFixed()" << endl;
#endif
#ifdef MACHINE_1

//	ControllerSeg4::getInstance()->getTimer()->stop();
	//Unregister all segments' controllers
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg5::getInstance());

	//Start motor if there is worpieces on the machine
	//and machine was runnins before the slide had become full
	if (!ControllerSeg1::getInstance()->isFifoEmpty()
			|| !ControllerSeg2::getInstance()->isFifoEmpty()
			|| !ControllerSeg3::getInstance()->isFifoEmpty()
			|| !ControllerSeg5::getInstance()->isFifoEmpty()
			) {
		if (MainController::getInstance()->isRunning())
			HALAktorik::getInstance()->motor_on();
			MainController::getInstance()->resumeAllTimers();
		}
#endif
#ifdef MACHINE_2
	ControllerSeg4::getInstance()->getTimer()->stop();
	ControllerSeg4::getInstance()->removeFirsttWP();

	Dispatcher::getInstance()->registerHandler(ControllerSegM2::getInstance());
	Sender::getInstance()->send(MACHINE2_IS_READY);
#endif
if (!MainController::getInstance()->isErrorRegistered()) {
	//Error has been fixed, but not registered yet : red light flashes slowly.
	RedLightFlash::getInstance()->flash(RED,ONE_S);
} else{
	HALAktorik::getInstance()->red_Light_off();
}

	//Machine goes back to state running.
	new (this) RunningMachine();
}

/**
 * Register error when it is not yet fixed.
 */
void SlideHandling::resetPressed() {
#ifdef DEBUG_
	cout << "SlideHandling :: resetReleased" << endl;
#endif
	//Stop red light flashing
	RedLightFlash::getInstance()->stopFlashing();
	//Red light goes on
	HALAktorik::getInstance()->red_Light_on();
	//Reset LED goes on
	HALAktorik::getInstance()->Reset_LED_on();
	//Set error status to registered
	MainController::getInstance()->setErrorRegistered(true);

}

/**
 * Deconstructor has nothing to do.
 */
SlideHandling::~SlideHandling() {

}


/************************************************************************************
 	 	 	 	 	 	 TurningErrorHandling

 ************************************************************************************/


/**
 * Constructor stops machine and all timers and unregister all segments' controllers.
 * Controller of end line's segment stays registered to notify the main controller if workpiece is back.
 * Red light starts flashing quickly.
 */
TurningErrorHandling::TurningErrorHandling() {
#ifdef DEBUG_
	cout << "TurningErrorHandling :: Constructor" << endl;
#endif

	//Stop all timers
	MainController::getInstance()->stopAllTimers();
	//Unregister all segment's controllers, but not the controller of segment line end,
#ifdef MACHINE_1
	Dispatcher::getInstance()->removeHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->removeHandler(ControllerSeg4::getInstance());
#endif
	//Stop motor
	HALAktorik::getInstance()->motor_off();
	//Red light starts flashing quickly.
	RedLightFlash::getInstance()->flash(RED,HALF_S);
	//Reset LED goes off because it has to be pressed to register error
	HALAktorik::getInstance()->Reset_LED_off();
	//Start LED goes off. It has to be pressed to start machine again.
	HALAktorik::getInstance()->Start_LED_off();
	// set error status
	MainController::getInstance()->setErrorRegistered(false);
}

/**
 * When Start is pressed after an error related to timer, reset all segments' controllers
 * and register them by dispatcher again.
 */
void TurningErrorHandling::startPressed() {
#ifdef DEBUG_
	cout << "TurningErrorHandling :: startPressed" << endl;
#endif

#ifdef MACHINE_1
	//Reset all controllers.
	ControllerSeg1::getInstance()->reset();
	ControllerSeg2::getInstance()->reset();
	ControllerSeg3::getInstance()->reset();
	ControllerSeg4::getInstance()->reset();

	//Register all controllers by dispatcher again.
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());
	HALAktorik::getInstance()->red_Light_off();
#endif
	//Turn red light of in case error has been registered.
	HALAktorik::getInstance()->red_Light_off();
	if (!MainController::getInstance()->isErrorRegistered()) {
		//Error has been fixed, but not registered yet : red light flashes slowly.
		RedLightFlash::getInstance()->flash(RED,ONE_S);
	}else {
		HALAktorik::getInstance()->red_Light_off();
	}

	//Start LED goes on.
	HALAktorik::getInstance()->Start_LED_on();

	//Machine goes back to state running.
	new (this) RunningMachine;
}

/**
 * Register error when it is not yet fixed.
 */
void TurningErrorHandling::resetPressed() {
#ifdef DEBUG_
	cout << "TurningErrorHandling :: resetPressed" << endl;
#endif
	//Stop red light flashing
	RedLightFlash::getInstance()->stopFlashing();
	//Red light goes on.
	HALAktorik::getInstance()->red_Light_on();
	//Reset LED goes on.
	HALAktorik::getInstance()->Reset_LED_on();
	//Set error status to registered
	MainController::getInstance()->setErrorRegistered(true);
}

/**
 * If the workpiece is put back in the line end, recover machine's state.
 */
void TurningErrorHandling::inLineEnd() {
#ifdef DEBUG_
	cout << "TurningErrorHandling :: inLineEnd" << endl;
#endif
	//Start motor and resumer all timers if the machine was running before
	//the error had occured
	if (MainController::getInstance()->isRunning()) {
		HALAktorik::getInstance()->motor_on();
		MainController::getInstance()->resumeAllTimers();
	}
	//Register all segments' controllers
	Dispatcher::getInstance()->registerHandler(ControllerSeg1::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg2::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg3::getInstance());
	Dispatcher::getInstance()->registerHandler(ControllerSeg4::getInstance());

	if (!MainController::getInstance()->isErrorRegistered()) {
		//Error has been fixed, but not registered yet : red light flashes slowly.
		RedLightFlash::getInstance()->flash(RED,ONE_S);
	}else {
		HALAktorik::getInstance()->red_Light_off();
	}


	//Machine goes back to running state.
	new (this) RunningMachine();
}
/**
 * Deconstructor has nothing to do.
 */
TurningErrorHandling::~TurningErrorHandling() {

}



/************************************************************************************
 	 	 	 	 	 	 	 	 Stop

 ************************************************************************************/
/**
 * Constructor has nothing to do.
 */
Stop::Stop() {
#ifdef DEBUG_
	cout << "Stop :: Constructor" << endl;
#endif

}

/**
 * Recover machine's state if start button is pressed.
 */
void Stop::startPressed() {
	//Run motor an resumer timers if machine was running.
	if (MainController::getInstance()->isRunning()) {
		HALAktorik::getInstance()->motor_on();
		MainController::getInstance()->resumeAllTimers();
	}

	//Start LED goes on.
	HALAktorik::getInstance()->Start_LED_on();
	//Register all segments' controllers.
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

	//Machine goes back to running state.
	new (this) RunningMachine();
}

/**
 * Constructor has nothing to do.
 */
Stop::~Stop() {

}

/************************************************************************************
 	 	 	 	 	 	 	 Emergency

 ************************************************************************************/
/**
 * Constructor has nothing to do.
 */
Emergency::Emergency() {
#ifdef DEBUG_
	cout << "Emergency :: Constructor" << endl;
#endif
}

/**
 * If EStop button is pulled out, machine goes to a new state.
 */
void Emergency::EStopReleased() {
	new (this) WaitingForReset();
}

/**
 * Deconstructor has nothing to do.
 */
Emergency::~Emergency() {

}


/************************************************************************************
 	 	 	 	 	 	 	 WaitingForReset

 ************************************************************************************/

/**
 * Constructor has nothing to do.
 */
WaitingForReset::WaitingForReset() {
#ifdef DEBUG_
	cout << "WaitingForReset :: Constructor" << endl;
#endif
}

/**
 * When Reset button is pressed, recover machine's state.
 */
void WaitingForReset::resetPressed() {
#ifdef DEBUG_
	cout << "WaitingForReset :: resetPressed " << endl;
#endif

	//Start motor and resume timers if machine was running
	if (MainController::getInstance()->isRunning()) {
		HALAktorik::getInstance()->motor_on();
		MainController::getInstance()->resumeAllTimers();
	}

	//Start LED goes on.
	HALAktorik::getInstance()->Start_LED_on();
	//Reset LED goes on.
	HALAktorik::getInstance()->Reset_LED_on();

	//Register all segments' controllers.
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
	//set error status
//	MainController::getInstance()->setErrorRegistered(true);

	//Machine goes back to running state.
	new (this) RunningMachine();
}

/**
 * Deconstructor has nothing to do.
 */
WaitingForReset::~WaitingForReset() {

}
