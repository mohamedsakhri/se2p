/*
 * @file 	ControllerSegM2.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 14, 2012
 *
 * This class represents the controller of Machine 2.
 */

#define DISPATCHER_TEST
#define DEBUG_

#include "ControllerSegM2.h"

Mutex ControllerSegM2::controllerSegM2_mutex_ = Mutex();
ControllerSegM2* ControllerSegM2::controllerSegM2_instance_ = NULL ;

/*
 *
 */
ControllerSegM2::ControllerSegM2() {
	ctr_id_ = CONTROLLER_SEGM2;
	state_ = new WaitForLineStart();
	init();
}

/*
 *
 */
ControllerSegM2* ControllerSegM2::getInstance() {

	if (!controllerSegM2_instance_) {
		controllerSegM2_mutex_.lock();
		if (!controllerSegM2_instance_) {
			controllerSegM2_instance_ = new ControllerSegM2;
		}
		controllerSegM2_mutex_.unlock();
	}
	return controllerSegM2_instance_;
}


/**
 * Do some initialization work
 */
void ControllerSegM2::init(){

	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("ControllerSegM2 : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "ControllerSegM2 attached to channelId: " << con_id_ << endl;
#endif
}

/*
 *
 */
void ControllerSegM2::wpIsComming() {
	state_->wpIsComming();
}

/*
 *
 */
void ControllerSegM2::inLineStart(){
	state_->inLineStart();
}

/*
 *
 */
void ControllerSegM2::inHeightMeasurement(){
	state_->inHeightMeasurement();
}

/*
 *
 */
void ControllerSegM2::outHeightMeasurement(){
	state_->outHeightMeasurement();
}

/*
 *
 */
void ControllerSegM2::inToleranceRange(){
	state_->inToleranceRange();
}

/*
 *
 */
void ControllerSegM2::isMetal(){
	state_->isMetal();
}

/*
 *
 */
void ControllerSegM2::outSwitch(){
	state_->outSwitch();
}

/*
 *
 */
void ControllerSegM2::inSwitch(){
	state_->inSwitch();
}

///*
// *
// */
//void ControllerSegM2::outSlide(){
//	state_->outSlide();
//}

/*
 *
 */
void ControllerSegM2::outLineEnd(){
	state_->outLineEnd();
}

/**
 * Send a message to Dispatcher
 */
int ControllerSegM2::sendMsg2Dispatcher(int message){

	if (-1 == MsgSendPulse(con_id_,SIGEV_PULSE_PRIO_INHERIT, CONTROLLER_CODE, message )) {
		perror("ControllerSegM2 : MsgSendPulse");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_
		cout << "ControllerSegM2: message sent to dispatcher: " << message << " code " << CONTROLLER_CODE << endl;
#endif
	}
	return 0;
}

//TODO communicate with Line 2
/**
 * Pass a workpiece from a segment to the next one
 */
void ControllerSegM2::passWP2Ctr()
{
//	controllerSegM2::getInstance()->addWP2List(getFirstWP());
}

/**
 * reset
 */
void ControllerSegM2::reset()
{
	this->wp_list_.clear();
	this->state_ = new WaitForLineStart();
}


/**
 * Delete instance of Istate
 */
ControllerSegM2::~ControllerSegM2() {
	delete state_ ;
}
