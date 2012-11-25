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

Mutex Dispatcher::dispatcher_mutex_ = Mutex();
Dispatcher* Dispatcher::dispatcher_instance_ = NULL;

/**
 * Create a channel and attach to it to get messages from Demultiplexer
 * and controller ( for errors i.e )
 */
Dispatcher::Dispatcher() {
	demultiplexer_ = Demultiplexer::getInstance();
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
	int pulse_message = -1;
	int pulse_code = -1;

	while (!isStopped()) {
		// Receive pulse messages from HAL Sensoric's (Interrupt handler) channel
		if (-1 == MsgReceivePulse(demultiplexer_->getChannelId(), &pulse, sizeof(pulse), NULL)) {
			if (isStopped()) {
				break; // channel destroyed, Thread ending
			}
			perror("Dispatcher: MsgReceivePulse");
			exit(EXIT_FAILURE);
		}

		// get message and its code. That's all what interest us in the pulse
		pulse_message = pulse.value.sival_int;
		pulse_code = pulse.code;
#ifdef DEBUG_
		cout << "Dispatcher: Receive code: " << pulse_code << " Message: " << pulse_message << endl;
#endif
		// Is message from Demultiplexer
		if ( pulse_code == DEMULTIPLEXER_CODE) {
			//find the event handler assigned to this message and call it
			/*
			 * ATTENTION PLZ : Some messages here might not be obligatory useful. See TODO
			 *
			 */
//TODO add function's call ( call-back mechanism )
//TODO filter which messages have to be treated here, some are may be useless
			switch (pulse_message) {
			case WP_IN_ENGINE_START :
				//TODO function call as said above. Same for all cases
				cout << "Dispatcher: WP in LS1" << endl;
				break;
			case WP_OUT_ENGINE_START :
				cout << "Dispatcher: WP out of LS1" << endl;
				break;
			case WP_IN_HEIGHT_M :
				break;
			case WP_OUT_HEIGHT_M:
				break;
			case WP_IN_TOLERANCE_R :
				break;
			case WP_NOT_IN_TOLERANCE_R :
				break;
			case WP_IS_METAL :
				break;
			case WP_NOT_METAL :
				break;
			case WP_IN_SWITCH :
				break;
			case WP_OUT_SWITCH :
				break;
			case WP_IN_SLIDE :
				cout << "Dispatcher: WP in Slide" << endl;
				break;
			case WP_OUT_SLIDE :
				cout << "Dispatcher: WP out Slide" << endl;
				break;
			case WP_IN_ENGINE_END :
				break;
			case WP_OUT_ENGINE_END:
				break;
			case START_PRESSED:
				break;
			case START_RELEASED:
				break;
			case STOP_PRESSED:
				break;
			case STOP_RELEASED:
				break;
			case RESET_PRESSED:
				break;
			case RESET_RELEASED:
				break;
			case E_STOP_PRESSED:
				break;
			case E_STOP_RELEASED:
				break;
			default :
			cout << " Unknown message" << endl; 	// Need some work. Or may be NOT!
			}
		} else {
			// Dispatcher can get messages from controller too, in case for errors i.e
			if (pulse_code == CONTROLLER_CODE) {
				switch(pulse_message) {
				case WP_IS_MISSING :
				break;
				case WP_IS_STRANGER :
				break;
				case WP_NOT_TURNED:
				break;
				case SLIDE_FULL:
				break;
				}
			}
		}
	}
}

void Dispatcher::shutdown(){

}

