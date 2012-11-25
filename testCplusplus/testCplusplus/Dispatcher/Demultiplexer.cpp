/*
 * @file Demultiplexer.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date Nov 25, 2012
 *
 *
 *	This Class implements the Demultiplexer's. It's a part of the Dispatcher's design pattern.
 *	Demultiplexer gets Events from HALsensoric, interprets them and send a message to dispatcher
 *	containing exactly what happened in the engine
 */

#include "Demultiplexer.h"

Mutex Demultiplexer::demultiplexer_mutex_ = Mutex();
Demultiplexer *Demultiplexer::demultiplexer_instance_ = NULL;

/**
 * get HALSensoric's and dispatcher's instances
 */
Demultiplexer::Demultiplexer() {
	hal_sensoric_ = HALSensoric::getInstance();
	dispatcher_ = Dispatcher::getInstance();

	// Connect to HALsensoric's channel to get pulses
	con_id_ = ConnectAttach(0, 0,dispatcher_->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (con_id_ == -1) {
		perror("Demultiplexer : ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
}

/**
 * free memory reserved by demultiplexer's instance
 */
// TODO do we have to delete Halsensoric's and dispatcher's instances too !?
Demultiplexer::~Demultiplexer() {
	delete demultiplexer_instance_;
	// detach connection with dispatcher's channel if it has been created
	if (con_id_) {
		ChannelDestroy(con_id_);
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
 * Here is where all the demultiplexer's work will be done
 * It gets pulses from Halsensoric, interprets them
 * and send the appropriate message to Dispatcher
 */
void Demultiplexer::execute(void* arg){

		struct _pulse pulse;
		int new_value = -1;
		int old_port_value; // used to compare new value from pulse with the old value to know what has been changed
		int changed_bits = -1;
		int current_bit = -1;
		int message = -1;	// message to be delivered to Dispatcher. See Messages.h

		// get the default value of port B and C.
		old_port_value = (in8(DIGITAL_CARD_CROUP0_PORTB)<<8)|(in8(DIGITAL_CARD_CROUP0_PORTC));

		while (!isStopped()) {

#ifdef DEBUG_
	cout << " waiting for MsgReceivePulse " << endl;
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
			changed_bits >>= 4;
			new_value >>= 4;

			#ifdef DEBUG_
				cout << "TEST port : " << hex << (int) pulse.code << " Value : "<< (int) new_value << endl;
			#endif

			// check all the 12 bits and assign the right message to be send
			for (int i=0;i<=12;i++){
				current_bit = (1<<i);
				if (changed_bits & current_bit){ // if the bit has changed
	//				cout << " current_bit: "<< hex << (int)current_bit << endl;
					switch (current_bit) {
					case START_BUTTON:		// Start Button
						if (new_value & START_BUTTON) {
							cout << "Start button pressed " << endl;
							message = START_PRESSED;
						}else {
							message = START_RELEASED;
						}
						break;
					case STOP_BUTTON:		//Stop Button
						if (!(new_value & STOP_BUTTON)) {
							cout << "Stop button pressed " << endl;
							message = STOP_PRESSED;
						}
						else {
							message = STOP_RELEASED;
						}
						break;
					case RESET_BUTTON:	 	//Reset Button
						if (new_value & RESET_BUTTON) {
							cout << "Reset button : Pressed " << endl;
							message = RESET_PRESSED;
						}
						else {
							cout << "Reset button : Released " << endl;
							message = RESET_RELEASED;
						}
						break;
					case E_STOP_BUTTON:		//E-Stop
						if (new_value & E_STOP_BUTTON) {
							cout << "E-Stop button : Released" << endl;
							message = E_STOP_RELEASED;
						} else {
							cout << "E-Stop button : Pressed" << endl;
							message = E_STOP_RELEASED;
						}
						break;
					case ENGINE_START:	//Light Barrier 1
						if ( !(new_value & ENGINE_START)) {
							cout << "Workpiece in LB 1 " << endl;
							message = WP_IN_ENGINE_START;
						}else {
							message = WP_OUT_ENGINE_START;
						}
						break;
					case HEIGHT_SENSOR:		//WP in HeightSensor  LB2
						if (!(new_value & HEIGHT_SENSOR)) {
							cout << "Workpiece in height measurement" << endl;
							message = WP_IN_HEIGHT_M;
						}else {
							cout << "Workpiece out height measurement" << endl;
							message = WP_OUT_HEIGHT_M;
						}
						break;
					case HEIGHT_STATUS:		//HeightSensor tolerance range
						if (new_value & HEIGHT_STATUS) {
							cout << "Workpiece's height in tolerance range"	<< endl;
							message = WP_IN_TOLERANCE_R;
						}
						else {
							cout << "Workpiece's height  NOT in tolerance range"	<< endl;
							message = WP_NOT_IN_TOLERANCE_R;
						}
						break;
					case WP_IS_IN_SWITCH:	// P in switch  LB3
						if (new_value & WP_IS_IN_SWITCH) {
							cout << "Workpiece's in Switch"	<< endl;
							message = WP_IN_SWITCH;
						}else {
							cout << "Workpiece's out Switch"	<< endl;
							message = WP_OUT_SWITCH;
						}
						break;
					case METAL_STATUS:		// Metal Sensor
						if (new_value & METAL_STATUS) {
							cout << "Workpiece is metal : YES" << endl;
							message = WP_IS_METAL;
						} else {
							cout << "Workpiece is metal : NO" << endl;
							message = WP_NOT_METAL;
						}
						break;
					case SWITCH_STATUS:		//Switch
						if (new_value & SWITCH_STATUS) {
							cout << "Switch is Open " << endl;
							message = SWITCH_IS_OPEN;
						} else {
							cout << "Switch is Closed" << endl;
							message = SWITCH_IS_CLOSED;
						}
						break;
					case SLIDE_STATUS:		//Slide
						if (new_value & SLIDE_STATUS) {
							cout << "Workpiece is out Slide" << endl;
							message = WP_OUT_SLIDE;

						} else {
							cout << "Workpiece is in Slide" << endl;
							message = WP_IN_SLIDE;
						}
						break;
					case ENGINE_END:	// LB end
						if (!(new_value & ENGINE_END)) {
							cout << "Workpiece IN the end of the band " << endl;
							message = WP_IN_ENGINE_END;
						}else {
							cout << "Workpiece OUT the end of the band " << endl;
							message = WP_OUT_ENGINE_END;
						}
						break;
					default :
					break;

					//Send the message to Dispatcher
					if (-1 == MsgSendPulse(dispatcher_->getChannelId(),SIGEV_PULSE_PRIO_INHERIT, DEMULTIPLEXER_CODE, message )) {
						if (isStopped()) {
							break; // channel destroyed, Thread ending
						}
						perror("Demultiplexer : MsgSendPulse");
						exit(EXIT_FAILURE);
					}
					} // switch (current_bit)
				} //if (changed_bits & current_bit)
			} // for
		} // while
}

/**
 *
 */
void Demultiplexer::shutdown(){

}
