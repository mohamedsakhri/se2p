/*
 * @file 	ControllerSeg4.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * This class represents the controller of the third segment which controls the slide area
 */

#define DISPATCHER_TEST
#define DEBUG_

#include "ControllerSeg4.h"

Mutex ControllerSeg4::controllerSeg4_mutex_ = Mutex();
ControllerSeg4* ControllerSeg4::controllerSeg4_instance_ = NULL ;

ControllerSeg4::ControllerSeg4() {
	ctr_id_ = CONTROLLER_SEG4;
	state_ = new SlideWait();
	init();
}

ControllerSeg4* ControllerSeg4::getInstance() {

	if (!controllerSeg4_instance_) {
		controllerSeg4_mutex_.lock();
		if (!controllerSeg4_instance_) {
			controllerSeg4_instance_ = new ControllerSeg4;
		}
		controllerSeg4_mutex_.unlock();
	}
	return controllerSeg4_instance_;
}


/**
 * Do some initialization work
 */
void ControllerSeg4::init(){

	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("ControllerSeg4 : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "ControllerSeg4 attached to channelId: " << con_id_ << endl;
#endif
}

void ControllerSeg4::inSlide()
{
	state_->inSlide();
}

void ControllerSeg4::outSlide()
{
	state_->outSlide();
}

//TODO to be updated for Error handling
void ControllerSeg4::startPressed() {
	HALAktorik::getInstance()->motor_on();
	HALAktorik::getInstance()->red_Light_off();
	HALAktorik::getInstance()->yellow_Light_off();
	HALAktorik::getInstance()->green_Light_on();
	HALAktorik::getInstance()->Start_LED_on();
}

//TODO to be updated for Error handling
void ControllerSeg4::stopPressed() {
	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->red_Light_off();
	HALAktorik::getInstance()->yellow_Light_off();
	HALAktorik::getInstance()->green_Light_off();
	HALAktorik::getInstance()->Start_LED_off();
}


//TODO to be updated for Error handling
void ControllerSeg4::EStopPressed() {
	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->Reset_LED_on();
}

//TODO to be updated for Error handling
void ControllerSeg4::EStopReleased() {
	HALAktorik::getInstance()->Reset_LED_off();
}

/**
 * Send a message to Dispatcher
 */
int ControllerSeg4::sendMsg2Dispatcher(int message){

	if (-1 == MsgSendPulse(con_id_,SIGEV_PULSE_PRIO_INHERIT, CONTROLLER_CODE, message )) {
		perror("ControllerSeg4 : MsgSendPulse");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_
		cout << "ControllerSeg4: message sent to dispatcher: " << message << " code " << CONTROLLER_CODE << endl;
#endif
	}
	return 0;
}

/**
 * Pass a workpiece from a segment to the next one
 */
void ControllerSeg4::passWP2Ctr()
{
//	ControllerSeg5::getInstance()->addWP2List(getFirstWP());
}

/**
 * Delete instance of Istate
 */
ControllerSeg4::~ControllerSeg4() {
	delete state_ ;
}
