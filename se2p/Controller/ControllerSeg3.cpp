/*
 * @file 	ControllerSeg3.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * This class represents the controller of the third segment which controls the switch area
 */

#define DISPATCHER_TEST
//#define DEBUG_

#include "ControllerSeg3.h"

Mutex ControllerSeg3::controllerSeg3_mutex_ = Mutex();
ControllerSeg3* ControllerSeg3::controllerSeg3_instance_ = NULL ;

/**
 * Initialize segment3's state
 */
ControllerSeg3::ControllerSeg3()
{
	ctr_id_ = CONTROLLER_SEG3;
	state_ = new WaitingSwitch();
	init();
}

/**
 * Return segment3's controller
 */
ControllerSeg3* ControllerSeg3::getInstance()
{
	if (!controllerSeg3_instance_) {
		controllerSeg3_mutex_.lock();
		if (!controllerSeg3_instance_) {
			controllerSeg3_instance_ = new ControllerSeg3;
		}
		controllerSeg3_mutex_.unlock();
	}
	return controllerSeg3_instance_;
}

/**
 * Do some initialization work :
  */
void ControllerSeg3::init()
{
	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("ControllerSeg3 : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "ControllerSeg3 attached to channelId: " << con_id_ << endl;
#endif
}

/**
 * WP is in switch
 */
void ControllerSeg3::inSwitch()
{
	state_->inSwitch();
}

/**
 * WP is out switch
 */
void ControllerSeg3::outSwitch()
{
	state_->outSwitch();
}

/**
 * Send a message to Dispatcher
 */
int ControllerSeg3::sendMsg2Dispatcher(int message) {
	if (-1 == MsgSendPulse(con_id_, SIGEV_PULSE_PRIO_INHERIT, CONTROLLER_CODE,
			message)) {
		perror("ControllerSeg3 : MsgSendPulse");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_
		cout << "ControllerSeg3: message sent to dispatcher: " << message << " code " << CONTROLLER_CODE << endl;
#endif
	}
	return 0;
}

/**
 * Pass a workpiece from a segment to the next one. Not used here.
 */
void ControllerSeg3::passWP2Ctr()
{

}

/**
 * Pass a workpiece from a segment to the next one
 */
void ControllerSeg3::passWP2Ctr(int controller_id)
{
	if (controller_id == CONTROLLER_SEG4)
		ControllerSeg4::getInstance()->addWP2List(this->getFirstWP());
	if (controller_id == CONTROLLER_SEG5)
		ControllerSeg5::getInstance()->addWP2List(this->getFirstWP());
}

/**
 * Reset controller
 */
void ControllerSeg3::reset() {
	this->wp_list_.clear();
	this->state_ = new WaitingSwitch();
}

/**
 * Delete instance of IState
 */
ControllerSeg3::~ControllerSeg3()
{
	delete state_ ;
}
