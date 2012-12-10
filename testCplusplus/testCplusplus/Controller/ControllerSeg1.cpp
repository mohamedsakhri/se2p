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
#include "ControllerSeg1.h"


Mutex ControllerSeg1::controllerSeg1_mutex_ = Mutex();
ControllerSeg1* ControllerSeg1::controllerSeg1_instance_ = NULL ;


ControllerSeg1::ControllerSeg1() {
	state_ = new StateLineStart();
	init();
}

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



void ControllerSeg1::inEngineStart()
{
	state_->inLineStart();
}

void ControllerSeg1::outEngineStart()
{
	state_->outLineStart();
//	this->passWP2Ctr();

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
 * Add an event to controller
 */
void ControllerSeg1::addEvent(int event_index)
{
	events_list_.push_back(event_index);
}

/**
 * Return al list of events the controller is registered to
 */
vector<int> ControllerSeg1::getEvents()
{
	return events_list_;
}

void ControllerSeg1::addWP2List(WorkPiece wp)
{
	wp_list_.push_back(wp);
}

WorkPiece ControllerSeg1::getLastWP()
{
	return wp_list_.at(wp_list_.size());
}


void ControllerSeg1::removeLastWP()
{
	wp_list_.pop_back();
}

void ControllerSeg1::passWP2Ctr()
{
	//TODO:
	//ctr->addWP2List(getLastWP());
}


ControllerSeg1::~ControllerSeg1()
{
	delete state_;
}
