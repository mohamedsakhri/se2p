/*
 * @file 	ControllerSeg5.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * This class represents the controller of the third segment which controls the line's end area
 */

#define DISPATCHER_TEST
#define DEBUG_

#include "ControllerSeg5.h"

Mutex ControllerSeg5::controllerSeg5_mutex_ = Mutex();
ControllerSeg5* ControllerSeg5::controllerSeg5_instance_ = NULL ;

/*
 *
 */
ControllerSeg5::ControllerSeg5()
{
	ctr_id_ = CONTROLLER_SEG5;
	machine2_ready_ = true;
	state_ = new WaitLineEndM1();
	init();
}

/*
 *
 */
ControllerSeg5* ControllerSeg5::getInstance()
{

	if (!controllerSeg5_instance_) {
		controllerSeg5_mutex_.lock();
		if (!controllerSeg5_instance_) {
			controllerSeg5_instance_ = new ControllerSeg5;
		}
		controllerSeg5_mutex_.unlock();
	}
	return controllerSeg5_instance_;
}

/**
 * Do some initialization work
 */
void ControllerSeg5::init()
{

	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("ControllerSeg5 : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "ControllerSeg5 attached to channelId: " << con_id_ << endl;
#endif
}

/*
 *
 */
void ControllerSeg5::inLineEnd()
{
	state_->inLineEnd();
}

/*
 *
 */
void ControllerSeg5::outLineEnd()
{
	state_->outLineEnd();
}

/*
 *
 */
void ControllerSeg5::m2isBusy()
{
	machine2_ready_ = false;
}

/*
 *
 */
void ControllerSeg5::m2isReady()
{
	machine2_ready_ = true;
	//state_->machine2IsReady();
	state_->messageReceived();
}

/*
 *
 */
bool ControllerSeg5::isMachin2Ready()
{
	return machine2_ready_;
}

/*
 *
 */
void ControllerSeg5::wpHasArrived()
{
	if (ControllerSeg1::getInstance()->isFifoEmpty()
			&& ControllerSeg2::getInstance()->isFifoEmpty()
			&& ControllerSeg3::getInstance()->isFifoEmpty()
			&& ControllerSeg4::getInstance()->isFifoEmpty()
			&& ControllerSeg5::getInstance()->isFifoEmpty()) {
		HALAktorik::getInstance()->motor_off();
	}
}

/**
 * Send a message to Dispatcher
 */
int ControllerSeg5::sendMsg2Dispatcher(int message)
{
	if (-1 == MsgSendPulse(con_id_,SIGEV_PULSE_PRIO_INHERIT, CONTROLLER_CODE, message )) {
		perror("ControllerSeg5 : MsgSendPulse");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_
		cout << "ControllerSeg5: message sent to dispatcher: " << message << " code " << CONTROLLER_CODE << endl;
#endif
	}
	return 0;
}

//TODO communicate with Line 2
/**
 * Pass a workpiece from a segment to the next one
 */
void ControllerSeg5::passWP2Ctr()
{
	cout << "ControllerSeg5::passWP2Ctr: ID: " << getFirstWP()->getId() << " TOL: " << getFirstWP()->getIs_inTolleranceRange() << endl;
	ControllerSegM2::getInstance()->addWP2List(this->getFirstWP());
}

/**
 * Delete instance of Istate
 */
ControllerSeg5::~ControllerSeg5()
{
	delete state_ ;
}
