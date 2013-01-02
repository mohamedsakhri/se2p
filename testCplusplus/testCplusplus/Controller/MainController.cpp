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
#define DISPATCHER_TEST
#define DEBUG_

#include "MainController.h"
#include "MainState.h"

Mutex MainController::mainController_mutex_ = Mutex();
MainController* MainController::mainController_instance_ = NULL ;

/*
 *
 */
MainController::MainController() {
	ctr_id_ = MAIN_CONTROLLER;
	state_ = new InitState();
	init();
}

/*
 *
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
 * Do some initialization work
 */
void MainController::init(){

	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("MainController : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "MainController attached to channelId: " << con_id_ << endl;
#endif
}

/*
 *
 */
void MainController::startPressed()
{
	state_->startPressed();
}

/*
 *
 */
void MainController::stopPressed()
{
	state_->stopPressed();
}

/*
 *
 */
void MainController::resetPressed()
{
	state_->resetPressed();
}

void MainController::resetReleased()
{
	state_->resetReleased();
}
/*
 *
 */
void MainController::EStopPressed()
{
	state_->EStopPressed();
}

/*
 *
 */
void MainController::EStopReleased()
{
	state_->EStopReleased();
}

/*
 *
 */
void MainController::isMissing()
{
	state_->error();
}

/*
 *
 */
void MainController::isStranger()
{
	state_->error();
}

/*
 *
 */
void MainController::slideFull()
{
	state_->error();
}

/*
 *
 */
void MainController::notTurned()
{
	state_->error();
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
// in case of problem : remove it and use addWP2List directly from state
void MainController::passWP2Ctr()
{
#ifdef DEBUG_
	cout << "MainController::passWP2Ctr: ID: " << getFirstWP()->getId() << " TOL: " << getFirstWP()->getIs_inTolleranceRange() << endl;
#endif
}

/**
 * Delete instance of IState
 */
MainController::~MainController()
{
	delete state_;
}
