/*
 * @file 	ControllerSeg1.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Nov 26, 2012
 *
 * This class represents the controller of the first segment which controls the line's start area.
 */

#define DISPATCHER_TEST
#define DEBUG_

#include "ControllerSeg1.h"

Mutex ControllerSeg1::controllerSeg1_mutex_ = Mutex();
ControllerSeg1* ControllerSeg1::controllerSeg1_instance_ = NULL ;

/*
 *
 */
ControllerSeg1::ControllerSeg1() {
	ctr_id_ = CONTROLLER_SEG1;
	state_ = new StateLineStart();
	init();
}

/*
 *
 */
ControllerSeg1* ControllerSeg1::getInstance() {

	if (!controllerSeg1_instance_) {
		controllerSeg1_mutex_.lock();
		if (!controllerSeg1_instance_) {
			controllerSeg1_instance_ = new ControllerSeg1;
		}
		controllerSeg1_mutex_.unlock();
	}
	return controllerSeg1_instance_;
}

/**
 * Do some initialization work
 */
void ControllerSeg1::init(){

	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("ControllerSeg1 : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "ControllerSeg1 attached to channelId: " << con_id_ << endl;
#endif
}

/*
 *
 */
void ControllerSeg1::inLineStart()
{
	state_->inLineStart();
}

/*
 *
 */
void ControllerSeg1::outLineStart()
{
	state_->outLineStart();
}

/**
 * Send a message to Dispatcher
 */
int ControllerSeg1::sendMsg2Dispatcher(int message){

	if (-1 == MsgSendPulse(con_id_,SIGEV_PULSE_PRIO_INHERIT, CONTROLLER_CODE, message )) {
		perror("ControllerSeg1 : MsgSendPulse");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_
		cout << "ControllerSeg1: message sent to dispatcher: " << message << " code " << CONTROLLER_CODE << endl;
#endif
	}
	return 0;
}


/**
 * Pass a workpiece from a segment to the next one
 */
// in case of problem : remove it and use addWP2List directly from state
void ControllerSeg1::passWP2Ctr()
{
#ifdef DEBUG_
	cout << "ControllerSeg1 :: passWP2Ctr" << endl;
#endif

	ControllerSeg2::getInstance()->addWP2List(this->getFirstWP());
}

/**
 * Delete instance of IState
 */
ControllerSeg1::~ControllerSeg1()
{
	delete state_;
}
