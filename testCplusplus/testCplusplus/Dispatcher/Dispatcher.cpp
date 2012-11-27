/*
 * @file Dispatcher.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date Nov 25, 2012
 *
 *
 *	This Class implements the Dispatcher's design pattern.
 *	Dispatcher gets messages from Demultiplexer ( and Controller )
 *	and execute a call-back to the right event handler(function) registred in its event handler table
 */

#include "Dispatcher.h"

#define DEBUG_

using namespace std;

Mutex Dispatcher::dispatcher_mutex_ = Mutex();
Dispatcher* Dispatcher::dispatcher_instance_ = NULL;

/**
 * Create a channel and attach to it to get messages from Demultiplexer
 * and controller ( for errors i.e )
 */
Dispatcher::Dispatcher() {
	demultiplexer_ = Demultiplexer::getInstance();

	initPt2FuncArray();
}

/**
 * free memory used by dispatcher's instance
 * detach from the channel and destroy it
 */
Dispatcher::~Dispatcher() {
	delete dispatcher_instance_;
	if (con_id_) {
		ConnectDetach_r(con_id_);
		ChannelDestroy(channel_id_);
	}
}
/**
 * return an Instance of the Dispatcher
 * At most one instance of Dispatcher will be created.
 * If no instance has been created yet, a new instance has to be created.
 * Otherwise the already created instance will be returned.
 */

Dispatcher* Dispatcher::getInstance() {
#ifdef DEBUG_
	cout << "Dispatcher started" << endl;
#endif
	if (!dispatcher_instance_) {
		dispatcher_mutex_.lock();
		if (!dispatcher_instance_) {
			dispatcher_instance_ = new Dispatcher;
		}
		dispatcher_mutex_.unlock();
	}

	return dispatcher_instance_;
}

/**
 * Return channel id. It will be used from outside to connect to dispatcher's channel
 */
int Dispatcher::getChannelId() {
	return channel_id_;
}

/**
 * All the Dispatcher's work will be done here
 * It gets messages from its channel and make call-backs using its event handker table
 */
void Dispatcher::execute(void* arg){
#ifdef DEBUG_
	cout << "Start dispatcher thread" << endl;
#endif

	demultiplexer_->start(NULL);

	// Connect to Demultiplexer's channel to get pulses
	con_id_ = ConnectAttach(0, 0,demultiplexer_->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("Dispatcher : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}


	struct _pulse pulse;
	int pulse_message_id = -1;
	int pulse_code = -1;

	while (!isStopped()) {
		cout << "Dispatcher : msgReceivePulse waiting... " << endl;

		// Receive pulse messages from HAL Sensoric's (Interrupt handler) channel
		if (-1 == MsgReceivePulse(demultiplexer_->getChannelId(), &pulse, sizeof(pulse), NULL)) {
			if (isStopped()) {
				break; // channel destroyed, Thread ending
			}
			perror("Dispatcher: MsgReceivePulse");
			exit(EXIT_FAILURE);
		}

		// get message and its code. That's all what interest us in the pulse
		pulse_message_id = pulse.value.sival_int;
		pulse_code = pulse.code;
#ifdef DEBUG_
		cout << "Dispatcher: Receive code: " << pulse_code << " Message: " << pulse_message_id << endl;
#endif

		unsigned int i = 0;
		for ( i; i < CTRList[pulse_message_id].size(); i++) {
			HALCallInterface& halCal = *CTRList[pulse_message_id].at(i);
			cout << " CTRL::iterator : " << i << endl;
			(halCal.*pt2FuncArray[pulse_message_id])();
		}
	}
}

/**
* Assign each item in pt2funcArray to the appropriate HALCallInterface's function
* Using messages as index makes it easy to follow and update the array
*/
void Dispatcher::initPt2FuncArray () {
	// Not all entries are defined and used now. This is just the Sensoric's part
	pt2FuncArray[WP_IN_ENGINE_START] 	= &HALCallInterface::inEngineStart;
	pt2FuncArray[WP_OUT_ENGINE_START] 	= &HALCallInterface::outEngineStart;
	pt2FuncArray[WP_IN_HEIGHT_M] 		= &HALCallInterface::inHeightMeasurement;
	pt2FuncArray[WP_OUT_HEIGHT_M] 		= &HALCallInterface::outHeightMeasurement;
	pt2FuncArray[WP_IN_TOLERANCE_R] 	= &HALCallInterface::inToleranceRange;
	pt2FuncArray[WP_NOT_IN_TOLERANCE_R] = &HALCallInterface::notInToleranceRange;
	pt2FuncArray[WP_IS_METAL] 			= &HALCallInterface::isMetal;
	pt2FuncArray[WP_NOT_METAL] 			= &HALCallInterface::notMetal;
	pt2FuncArray[WP_IN_SWITCH] 			= &HALCallInterface::inSwitch;
	pt2FuncArray[WP_OUT_SWITCH] 		= &HALCallInterface::outSwitch;
	pt2FuncArray[SWITCH_IS_OPEN] 		= &HALCallInterface::switchOpen;
	pt2FuncArray[SWITCH_IS_CLOSED] 		= &HALCallInterface::switchClosed;
	pt2FuncArray[WP_IN_SLIDE] 			= &HALCallInterface::inSlide;
	pt2FuncArray[WP_OUT_SLIDE] 			= &HALCallInterface::outSlide;
	pt2FuncArray[WP_IN_ENGINE_END] 		= &HALCallInterface::inEngineEnd;
	pt2FuncArray[WP_OUT_ENGINE_END] 	= &HALCallInterface::outEngineEnd;

	pt2FuncArray[START_PRESSED]			= &HALCallInterface::startPressed;
	pt2FuncArray[START_RELEASED]		= &HALCallInterface::startReleased;
	pt2FuncArray[STOP_PRESSED]			= &HALCallInterface::stopPressed;
	pt2FuncArray[STOP_RELEASED]			= &HALCallInterface::stopReleased;
	pt2FuncArray[RESET_PRESSED]			= &HALCallInterface::resetPressed;
	pt2FuncArray[RESET_RELEASED]		= &HALCallInterface::resetReleased;
	pt2FuncArray[E_STOP_PRESSED]		= &HALCallInterface::EStopPressed;
	pt2FuncArray[E_STOP_RELEASED]		= &HALCallInterface::EStopReleased;


//TODO More items are supposed to be added if we want to assign some error's treatment here too
}

/**
 * Register handler "controller" in Dispatcher's list of controllers
 */
void Dispatcher::registerHandler(HALCallInterface* handler){
	unsigned int i;
	vector<int> events = handler->getEvents();

	for ( i = 0 ; i < events.size(); i++){
		CTRList[events.at(i)].push_back(handler);
	}
}

/**
 * Remove handler from Dispatcher's list of Controllers
 */
void Dispatcher::removeHandler(HALCallInterface* handler){
//	CTRList.remove(handler);
}
void Dispatcher::shutdown(){

}

