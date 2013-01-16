/*
 * @file 	ControllerSeg2.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * This class represents the controller of the first segment which controls the height area.
 */

#define DISPATCHER_TEST
#define DEBUG_

#include "ControllerSeg2.h"

Mutex ControllerSeg2::controllerSeg2_mutex_ = Mutex();
ControllerSeg2* ControllerSeg2::controllerSeg2_instance_ = NULL ;

/**
 * Initialize segment2's state
 */
ControllerSeg2::ControllerSeg2()
{
	ctr_id_ = CONTROLLER_SEG2;
	state_ = new WaitingHeightM1();
	init();
}

/*
 * Retunr segment2's controller
 */
ControllerSeg2* ControllerSeg2::getInstance() {
	if (!controllerSeg2_instance_) {
		controllerSeg2_mutex_.lock();
		if (!controllerSeg2_instance_) {
			controllerSeg2_instance_ = new ControllerSeg2;
		}
		controllerSeg2_mutex_.unlock();
	}
	return controllerSeg2_instance_;
}

/**
 * Do some initialization work : Connect to demultiplexer's channel
 */
void ControllerSeg2::init()
{
	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("ControllerSeg2 : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "ControllerSeg2 attached to channelId: " << con_id_ << endl;
#endif
}

/**
 * WP is in Height measurement : Segment's state goes to heightMeaseurement state
 */
void ControllerSeg2::inHeightMeasurement()
{
	state_->inHeightMeasurement();
}

/**
 * WP is out Height measurement
 */
void ControllerSeg2::outHeightMeasurement()
{
	state_->outHeightMeasurement();
}

/**
 * WP is in Tolerance range
 */
void ControllerSeg2::inToleranceRange()
{
	state_->inToleranceRange();
}

/**
 * WP is not in Tolerance range
 */
void ControllerSeg2::notInToleranceRange()
{
//	state_->notInToleranceRange();
}

/**
 * Send a message to Dispatcher
 */
int ControllerSeg2::sendMsg2Dispatcher(int message)
{

	if (-1 == MsgSendPulse(con_id_,SIGEV_PULSE_PRIO_INHERIT, CONTROLLER_CODE, message )) {
		perror("ControllerSeg2 : MsgSendPulse");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_
		cout << "ControllerSeg2: message sent to dispatcher: " << message << " code " << CONTROLLER_CODE << endl;
#endif
	}
	return 0;
}

/**
 * Pass a workpiece from a segment to the next one
 */
void ControllerSeg2::passWP2Ctr()
{
#ifdef DEBUG_
//	cout << "ControllerSeg2::passWP2Ctr: ID: " << getFirstWP()->getId() << " TOL: " << getFirstWP()->getIs_inTolleranceRange() << endl;
#endif
	ControllerSeg3::getInstance()->addWP2List(this->getFirstWP());
}

void ControllerSeg2::reset() {
	this->wp_list_.clear();
	this->state_ = new WaitingHeightM1();
}

/**
 * Delete instance of Istate
 */
ControllerSeg2::~ControllerSeg2()
{
	delete state_ ;
}
