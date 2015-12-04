/*
 * @file Demultiplexer.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date 	Nov 25, 2012
 *
 *
 *	This Class implements the Demultiplexer's. It's a part of the Dispatcher's design pattern.
 *	Demultiplexer gets Events from HALsensoric, interprets them and send a message to dispatcher
 *	containing exactly what happened in the engine
 */

#include "Demultiplexer.h"

//#define DEBUG_

Mutex Demultiplexer::demultiplexer_mutex_ = Mutex();
Demultiplexer *Demultiplexer::demultiplexer_instance_ = NULL;

/**
 * Call init ro do some initialization work
 */
Demultiplexer::Demultiplexer() {
#ifdef DEBUG_
	cout << "Demultiplexer created" << endl;
#endif

	init();
}


/**
 * Do some initialization work :
 * Get HALSensoric instance
 * Create a channel and attach to it
 */
void Demultiplexer::init(){
	hal_sensoric_ = HALSensoric::getInstance();

	channel_id_ = ChannelCreate(0);
		if(channel_id_ == -1) {
			perror ("Demultiplexer: ChannelCreat failed : ");
			exit(EXIT_FAILURE);
		}

		con_id_ = ConnectAttach(0, 0, channel_id_, _NTO_SIDE_CHANNEL, 0);
		if (con_id_ == -1) {
			perror("Demultiplexer : ConnectAttach failed : ");
			exit(EXIT_FAILURE);
		}
#ifdef DEBUG_
		cout << "Demultiplexer attached to channelId: " << channel_id_ << endl;
#endif
}


/**
 * free memory reserved by demultiplexer's instance
 */
Demultiplexer::~Demultiplexer() {
#ifdef DEBUG_
	cout << "Demultiplexer deleted" << endl;
#endif

	delete demultiplexer_instance_;
	// detach connection channel if it has been created
	if (con_id_) {
		ConnectDetach(con_id_);
		ChannelDestroy(channel_id_);
	}
}

/**
 * return an Instance of the Demultiplexer
 * At most one instance of Demultiplexer will be created.
 * If no instance has been created yet, a new instance has to be created.
 * Otherwise the already created instance will be returned.
 *
 */
Demultiplexer* Demultiplexer::getInstance() {
#ifdef DEBUG_
	cout << "Demultiplexer instance" << endl;
#endif
	if (!demultiplexer_instance_) {
		demultiplexer_mutex_.lock();
		if (!demultiplexer_instance_) {
			demultiplexer_instance_ = new Demultiplexer;
		}
		demultiplexer_mutex_.unlock();
	}

	return demultiplexer_instance_;
}

/**
 * Return demultiplex'r channel id
 */
int Demultiplexer::getChannelId(){
	return channel_id_;
}

/**
 * Here is where all the demultiplexer's work will be done
 * It gets pulses from Halsensoric, interprets them
 * and send the appropriate message to Dispatcher
 */
void Demultiplexer::execute(void* arg){
#ifdef DEBUG_
		cout << "Demultiplexer thread started" << endl;
#endif
		struct _pulse pulse;
		int new_value = -1;
		int old_port_value; 	// used to compare new value from pulse with the old value to know what has been changed
		int changed_bits = -1;	// bits which had been changed by interrupt from old value
		int current_bit = -1;	// needed in for-loop
		int message = -1;		// message to be delivered to Dispatcher. See Messages.h


		// get the default value of port B and C. This will be called once
		old_port_value = (in8(DIGITAL_CARD_CROUP0_PORTB)<<8)|(in8(DIGITAL_CARD_CROUP0_PORTC));

		while (!isStopped()) {

#ifdef DEBUG_
	cout << "Demultiplexer: waiting for MsgReceivePulse " << endl;
#endif

			// Receive pulse messages from HAL Sensoric's (Interrupt handler) channel
			if (-1 == MsgReceivePulse(hal_sensoric_->getChannelId(), &pulse,
					sizeof(pulse), NULL)) {
				if (isStopped()) {
					break; // channel destroyed, Thread ending
				}
				perror("Demultiplexer: MsgReceivePulse");
				exit(EXIT_FAILURE);
			}

			new_value = pulse.value.sival_int;
			changed_bits = new_value ^ old_port_value;	// which bits have been changed
			old_port_value = pulse.value.sival_int;		// update old value with the new one

			// shift 12 bits right. First 4 bits from port C are useless here
//TODO is 4 here a magic number !!
			changed_bits >>= 4;
			new_value >>= 4;

#ifdef DEBUG_
	cout << "Demultplexer: port : " << hex << (int) pulse.code << " Value : "<< (int) new_value << endl;
#endif

			// check all the 12 bits and assign the right message to be send
			for (int i=0;i<=12;i++){
				current_bit = (1<<i);
				if (changed_bits & current_bit){ // if the bit has changed
#ifdef DEBUG_
	cout << " current_bit: "<< hex << (int)current_bit << endl;
#endif
					switch (current_bit) {
					case START_BUTTON:		// Start Button
						if (new_value & START_BUTTON) {
							message = START_PRESSED;
						}else {
							message = START_RELEASED;
						}
						sendMsg2Dispatcher(message);
						break;
					case STOP_BUTTON:		//Stop Button
						if (!(new_value & STOP_BUTTON)) {
							message = STOP_PRESSED;
						}
						else {
							message = STOP_RELEASED;
						}
						sendMsg2Dispatcher(message);
						break;
					case RESET_BUTTON:	 	//Reset Button
						if (new_value & RESET_BUTTON) {
							message = RESET_PRESSED;
						}
						else {
							message = RESET_RELEASED;
						}
						sendMsg2Dispatcher(message);
						break;
					case E_STOP_BUTTON:		//E-Stop
						if (new_value & E_STOP_BUTTON) {
							message = E_STOP_RELEASED;
						} else {
							message = E_STOP_PRESSED;
						}
						sendMsg2Dispatcher(message);
						break;
					case ENGINE_START:	//Light Barrier 1
						if ( !(new_value & ENGINE_START)) {
							message = WP_IN_ENGINE_START;
						}else {
							message = WP_OUT_ENGINE_START;
						}
						sendMsg2Dispatcher(message);
						break;
					case HEIGHT_SENSOR:		//WP in HeightSensor  LB2
						if (!(new_value & HEIGHT_SENSOR)) {
							message = WP_IN_HEIGHT_M;
//							cout << "Demultiplexer: WP_IN_HEIGHT_M" <<endl;

						}else {
							message = WP_OUT_HEIGHT_M;
//							cout << "Demultiplexer: WP_OUT_HEIGHT_M" <<endl;

						}
						sendMsg2Dispatcher(message);
						break;
					case HEIGHT_STATUS:		//HeightSensor tolerance range
						if (new_value & HEIGHT_STATUS) {
							message = WP_IN_TOLERANCE_R;
//							cout << "Demultiplexer: WP_INTOL" <<endl;
						}
						else {
							message = WP_NOT_IN_TOLERANCE_R;
//							cout << "Demultiplexer: WP_NOT_INTOL" <<endl;
						}
						sendMsg2Dispatcher(message);
						break;
					case WP_IS_IN_SWITCH:	// P in switch  LB3
						if (new_value & WP_IS_IN_SWITCH) {
							message = WP_OUT_SWITCH;
						}else {
							message = WP_IN_SWITCH;
						}
						sendMsg2Dispatcher(message);
						break;
					case METAL_STATUS:		// Metal Sensor
						if (new_value & METAL_STATUS) {
							message = WP_IS_METAL;
						} else {
							message = WP_NOT_METAL;
						}
						sendMsg2Dispatcher(message);
						break;
					case SWITCH_STATUS:		//Switch
						if (new_value & SWITCH_STATUS) {
							message = SWITCH_IS_OPEN;
						} else {
							message = SWITCH_IS_CLOSED;
						}
						sendMsg2Dispatcher(message);
						break;
					case SLIDE_STATUS:		//Slide
						if (new_value & SLIDE_STATUS) {
							message = WP_OUT_SLIDE;

						} else {
							message = WP_IN_SLIDE;
						}
						sendMsg2Dispatcher(message);
						break;
					case ENGINE_END:	// LB end
						if (!(new_value & ENGINE_END)) {
							message = WP_IN_ENGINE_END;
						}else {
							message = WP_OUT_ENGINE_END;
						}
						sendMsg2Dispatcher(message);
						break;
					case WP_IS_MISSING:
						message = WP_IS_MISSING;
						sendMsg2Dispatcher(message);
						break;
					default :
					break;

					} // switch (current_bit)
				} //if (changed_bits & current_bit)
			} // for
		} // while
}

/**
 * Send a message to Dispatcher
 */
int Demultiplexer::sendMsg2Dispatcher(int message){

	if (-1 == MsgSendPulse(con_id_,SIGEV_PULSE_PRIO_INHERIT, DEMULTIPLEXER_CODE, message )) {
		if (isStopped()) {
			return -1; // channel destroyed, Thread ending
		}
		perror("Demultiplexer : MsgSendPulse");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_
		cout << "Demultiplexer: message sent to dispatcher: " << message << " code " << DEMULTIPLEXER_CODE << endl;
#endif
	}
	return 0;
}


/**
 *
 */
void Demultiplexer::shutdown(){

}
