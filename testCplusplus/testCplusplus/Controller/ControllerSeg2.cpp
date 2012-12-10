/*
 * @file 	Controller.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Nov 26, 2012
 *
 */

#define DISPATCHER_TEST
#include "ControllerSeg2.h"

Mutex ControllerSeg2::controllerSeg2_mutex_ = Mutex();
ControllerSeg2* ControllerSeg2::controllerSeg2_instance_ = NULL ;

ControllerSeg2::ControllerSeg2() {
	state_ = new StateHeight();
	init();
}

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
 * Do some initialization work
 */
void ControllerSeg2::init(){

	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("ControllerSeg2 : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "ControllerSeg2 attached to channelId: " << con_id_ << endl;
#endif
}

void ControllerSeg2::inHeightMeasurement()
{
	state_->inHeightMeasurement();
}

void ControllerSeg2::outHeightMeasurement()
{
	state_->outHeightMeasurement();
//	this->passWP2Ctr(height_state_->controller);
}

void ControllerSeg2::inToleranceRange()
{
	state_->inToleranceRange();
}

void ControllerSeg2::notInToleranceRange()
{
	state_->notInToleranceRange();
}

/**
 * Send a message to Dispatcher
 */
int ControllerSeg2::sendMsg2Dispatcher(int message){

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
 * Add an event to controller
 */
void ControllerSeg2::addEvent(int event_index)
{
	events_list_.push_back(event_index);
}

/**
 * Return al list of events the controller is registered to
 */
vector<int> ControllerSeg2::getEvents()
{
	return events_list_;
}

void ControllerSeg2::addWP2List(WorkPiece wp)
{
	wp_list_.push_back(wp);
}

WorkPiece ControllerSeg2::getLastWP()
{
	return wp_list_.at(wp_list_.size());
}


void ControllerSeg2::removeLastWP()
{
	wp_list_.pop_back();
}

void ControllerSeg2::passWP2Ctr(HALCallInterface* ctr)
{
	ctr->addWP2List(getLastWP());
}


ControllerSeg2::~ControllerSeg2() {
	delete state_ ;
}
