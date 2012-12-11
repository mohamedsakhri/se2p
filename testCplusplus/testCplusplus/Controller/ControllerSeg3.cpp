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
#define DEBUG_
#include "ControllerSeg3.h"

Mutex ControllerSeg3::controllerSeg3_mutex_ = Mutex();
ControllerSeg3* ControllerSeg3::controllerSeg3_instance_ = NULL ;

ControllerSeg3::ControllerSeg3() {
	state_ = new WaitingSwitch();
	init();
}

ControllerSeg3* ControllerSeg3::getInstance() {

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
 * Do some initialization work
 */
void ControllerSeg3::init(){

	con_id_ = ConnectAttach(0, 0, Demultiplexer::getInstance()->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("ControllerSeg3 : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "ControllerSeg3 attached to channelId: " << con_id_ << endl;
#endif
}

void ControllerSeg3::inSwitch()
{
	state_->inSwitch();
}

void ControllerSeg3::outSwitch()
{
	state_->outSwitch();
}

/**
 * Send a message to Dispatcher
 */
int ControllerSeg3::sendMsg2Dispatcher(int message){

	if (-1 == MsgSendPulse(con_id_,SIGEV_PULSE_PRIO_INHERIT, CONTROLLER_CODE, message )) {
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
 * Add an event to controller
 */
void ControllerSeg3::addEvent(int event_index)
{
	events_list_.push_back(event_index);
}

/**
 * Return al list of events the controller is registered to
 */
vector<int> ControllerSeg3::getEvents()
{
	return events_list_;
}

void ControllerSeg3::addWP2List(WorkPiece* wp)
{
#ifdef DEBUG_
	cout << "ControllerSeg3::addWP2List: ID: " << wp->getId() << " TOL: " << wp->getIs_inTolleranceRange() << endl;
#endif
	wp_list_.push_back(wp);
}

WorkPiece* ControllerSeg3::getLastWP()
{
//	return wp_list_.at(wp_list_.size());
	return wp_list_.front();
}


void ControllerSeg3::removeLastWP()
{
	if (!wp_list_.empty()){
#ifdef DEBUG_
			cout << "ControllerSeg3: WP: removed" << endl;
#endif
			wp_list_.erase(wp_list_.begin());
		}
	else{
		cout << "fifo in seg3 empty " << endl;
	}
}

void ControllerSeg3::passWP2Ctr()
{
//	ControllerSeg5::getInstance()->addWP2List(getLastWP());
}


ControllerSeg3::~ControllerSeg3() {
	delete state_ ;
}
