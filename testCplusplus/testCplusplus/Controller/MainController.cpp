/*
 * @file	MainController.cpp
 *
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 19, 2012
 *
 * Classes which represent the main controller
 *
 */

#define DEBUG_
#define MACHINE_1	// MainController for machine 1
//#define MACHINE_2	//MainController for machine 2

#include "MainController.h"
#include "MainState.h"

Mutex MainController::mainController_mutex_ = Mutex();
MainController* MainController::mainController_instance_ = NULL ;

/**
 * MainController's constructor
 */
MainController::MainController() {
	ctr_id_ = MAIN_CONTROLLER;
	state_ = new InitState();
	errorRegistered_ = false;
	init();
}

/**
 * Create or return mainctroller's instance
 */
MainController* MainController::getInstance() {

	if (!mainController_instance_) {
		mainController_mutex_.lock();
		if (!mainController_instance_) {
			mainController_instance_ = new MainController;
		}
		mainController_mutex_.unlock();
	}
	return mainController_instance_;
}

/**
 * Do some initialization work : Attach to Demultiplexer's channel
 */
void MainController::init() {
	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(),
			_NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("MainController : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
}

/**
 *
 */
void MainController::startPressed()
{
	state_->startPressed();
}

/**
 *
 */
void MainController::stopPressed()
{
	state_->stopPressed();
}

/**
 *
 */
void MainController::resetPressed()
{
	state_->resetPressed();
}

void MainController::resetReleased()
{
//	HALAktorik::getInstance()->Reset_LED_off();
}
/**
 *
 */
void MainController::EStopPressed()
{
	state_->EStopPressed();
	Sender::getInstance()->send(E_STOP_PRESSED_OTHER);
}

/**
 *
 */
void MainController::EStopReleased()
{
	state_->EStopReleased();
	Sender::getInstance()->send(E_STOP_RELEASED_OTHER);
}

/**
 *
 */
void MainController::EStopPressedOther()
{
	state_->EStopPressed();
}

/**
 *
 */
void MainController::EStopReleasedOther()
{
	state_->EStopReleased();
}

/**
 * When a workpiece disapears or take too much time to between two light's barrier
 */
void MainController::isMissing()
{
	state_->timeOutError();
}

/**
 * When a stranger workpiece appears on machine or arrives too quickly to light's barrier
 */
void MainController::isStranger()
{
	cout << "IS STRANGER" << endl;
	state_->timeOutError();
}

/**
 * Slide has been full
 */
void MainController::slideFull()
{
	state_->slideFull();
}

/**
 *
 */
void MainController::slideEmpty()
{
	state_->slideErrorFixed();

}

/**
 *
 */
void MainController::notTurned()
{
	state_->turningErrorHandling();
}

/**
 * Send a message to Dispatcher
 */
int MainController::sendMsg2Dispatcher(int message){

	if (-1 == MsgSendPulse(con_id_,SIGEV_PULSE_PRIO_INHERIT, CONTROLLER_CODE, message )) {
		perror("MainController : MsgSendPulse");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_
		cout << "MainController: message sent to dispatcher: " << message << " code " << CONTROLLER_CODE << endl;
#endif
	}
	return 0;
}


/**
 * Pass a workpiece from a segment to the next one
 */
void MainController::passWP2Ctr() {
#ifdef DEBUG_
	cout << "MainController :: passWP2Ctr" << endl;
#endif
}

/**
 * Pause all timers in the machine
 */
void MainController::pauseAllTimers(){
#ifdef MACHINE_1
	pauseTimers(ControllerSeg1::getInstance());
	pauseTimers(ControllerSeg2::getInstance());
	pauseTimers(ControllerSeg3::getInstance());
	pauseTimers(ControllerSeg4::getInstance());
	pauseTimers(ControllerSeg5::getInstance());

	// Pause timer assigned to controller4 : Timer to control if slide is full

		ControllerSeg4::getInstance()->getTimer()->pause();

	 // Pause timer assigned to controller : Timer to control if has been put back after turning it
		ControllerSeg5::getInstance()->getTimer()->pause();
#endif
#ifdef MACHINE_2
//	resumeTimers(ControllerSegM2::getInstance());
#endif
}

/**
 * Resume all timers in the machine
 */
void MainController::resumeAllTimers() {
#ifdef MACHINE_1
	resumeTimers(ControllerSeg1::getInstance());
	resumeTimers(ControllerSeg2::getInstance());
	resumeTimers(ControllerSeg3::getInstance());
	resumeTimers(ControllerSeg4::getInstance());
	resumeTimers(ControllerSeg5::getInstance());
	/*
	 * Resume timer assigned to controller4 : Timer to control if slide is full
	 */
	ControllerSeg4::getInstance()->getTimer()->resume();
	/*
	 * Resume timer assigned to controller : Timer to control if has been put back after turning it
	 */
		ControllerSeg5::getInstance()->getTimer()->resume();

#endif
#ifdef MACHINE_2
//	resumeTimers(ControllerSegM2::getInstance());
#endif
}

/**
 * Pause all timers in a segment controlled by ctr
 */
void MainController::pauseTimers(HALCallInterface* ctr)
{
	unsigned int i ;
	 // Pause all timers assigned to workpieces
	if (!ctr->isFifoEmpty()) {
		for ( i = 0; i < ctr->getWPList().size(); i++) {
			ctr->getWPList().at(i)->getTimer()->pause();
		}
	}
}

/**
 * Resume all timers in a segment controlled by ctr
 */
void MainController::resumeTimers(HALCallInterface* ctr)
{
	unsigned int i ;
	if (!ctr->isFifoEmpty()) {
		for ( i = 0; i < ctr->getWPList().size(); i++) {
			ctr->getWPList().at(i)->getTimer()->resume();
		}
	}
}


/**
 * Resume all timers in the machine
 */
void MainController::stopAllTimers() {
#ifdef MACHINE_1
	stopTimers(ControllerSeg1::getInstance());
	stopTimers(ControllerSeg2::getInstance());
	stopTimers(ControllerSeg3::getInstance());
	stopTimers(ControllerSeg4::getInstance());
	stopTimers(ControllerSeg5::getInstance());
	// Resume timer assigned to controller4 : Timer to control if slide is full
	if (ControllerSeg4::getInstance()->getControllerId()) {
		ControllerSeg4::getInstance()->getTimer()->stop();
	}
	 // Resume timer assigned to controller : Timer to control if has been put back after turning it
	if (ControllerSeg5::getInstance()->getControllerId()) {
		ControllerSeg5::getInstance()->getTimer()->stop();
	}
#endif

#ifdef MACHINE_2
//	stopTimers(ControllerSegM2::getInstance());
#endif
}

/**
 * Pause all timers in a segment controlled by ctr
 */
void MainController::stopTimers(HALCallInterface* ctr)
{
	unsigned int i ;
	 // Pause all timers assigned to workpieces
	if (!ctr->isFifoEmpty()) {
		for ( i = 0; i < ctr->getWPList().size(); i++) {
			ctr->getWPList().at(i)->getTimer()->stop();
		}
	}
}


/**
 * Delete instance of IState and detach connecntion to channel
 */
MainController::~MainController()
{
	delete state_;

	if (ConnectDetach(con_id_ == -1)) {
		perror("ConnectDetach error : ");
	}
}


