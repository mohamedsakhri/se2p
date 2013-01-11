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
#define MACHINE1

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
	state_->slideFull();
	Dispatcher::getInstance()->registerEvent(MainController::getInstance(), WP_OUT_SLIDE);
}

/*
 *
 */
void MainController::outSlide()
{
	// To be changed with error fixed
	state_->errorFixed();
	Dispatcher::getInstance()->removeEvent(MainController::getInstance(), WP_OUT_SLIDE);


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
	cout << "MainController :: passWP2Ctr" << endl;
#endif
}

/**
 *
 */
void MainController::pauseAllTimers(){
#ifdef MACHINE1
	pauseTimers(ControllerSeg1::getInstance());
	pauseTimers(ControllerSeg2::getInstance());
	pauseTimers(ControllerSeg3::getInstance());
	pauseTimers(ControllerSeg4::getInstance());
	pauseTimers(ControllerSeg5::getInstance());
#endif

#ifdef MACHINE2
	resumeTimers(ControllerSegM2::getInstance());
#endif

}

/**
 *
 */
void MainController::resumeAllTimers(){
#ifdef MACHINE1
	resumeTimers(ControllerSeg1::getInstance());
	resumeTimers(ControllerSeg2::getInstance());
	resumeTimers(ControllerSeg3::getInstance());
	resumeTimers(ControllerSeg4::getInstance());
	resumeTimers(ControllerSeg5::getInstance());
#endif

#ifdef MACHINE2
	resumeTimers(ControllerSegM2::getInstance());
#endif


}

/**
 *
 */
void MainController::pauseTimers(HALCallInterface* ctr)
{
	unsigned int i ;
	if (!ctr->isFifoEmpty()) {
		for ( i = 0; i < ctr->getWPList().size(); i++) {
			ctr->getWPList().at(i)->getTimer()->pause();
		}
	}
	//TODO pause CTR-timers
}

/**
 *
 */
void MainController::resumeTimers(HALCallInterface* ctr)
{
	unsigned int i ;
	if (!ctr->isFifoEmpty()) {
		for ( i = 0; i < ctr->getWPList().size(); i++) {
			ctr->getWPList().at(i)->getTimer()->resume();
		}
	}
	//TODO resume CTR-timers
}
/**
 * Delete instance of IState
 */
MainController::~MainController()
{
	delete state_;
}
