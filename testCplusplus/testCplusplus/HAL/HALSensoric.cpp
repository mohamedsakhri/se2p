/*
 * HALSensoric.cpp
 *
 *  Created on: 07.11.2012
 *      Author: aax877
 */

#include "HALSensoric.h"


Mutex HALSensoric::hal_Sensoric_mutex_ = Mutex();


HALSensoric::HALSensoric() {
	// TODO Auto-generated constructor stub

}

HALSensoric::~HALSensoric() {
	// TODO Auto-generated destructor stub
}


HALSensoric *HALSensoric::getInstance(){

	if (!hal_Sensoric_instance_) {
			hal_Aktorik_mutex_.lock();
			if (!hal_Sensoric_instance_) {
				hal_Sensoric_instance_ = new HALAktorik;
			}
			hal_Sensoric_mutex_.unlock();
		}


		return hal_Sensoric_instance_;
}



const struct sigevent *HALSensoric::ISR(void *arg, int id){

	uint8_t reg_stat;
	uint8 port_state;
	struct sigevent *event = (struct sigevent *)arg;

	/**
	 * read the interrupt register status
	 */
	reg_stat = in8 (INTERRUPT_STATUS_REG) & (BIT_1 | BIT_3);
	out8(DIO_BASE + OFFS_INT_STATUS, 0); // reset interr_register
	// if no interrupt from portC or portB ignore
	if (!reg_stat) {
		return (NULL);
	}

	switch (reg_stat) {
	case BIT_1:
		/** if the interrupt is from port B */
		port_state = in8(DIGITAL_CARD_CROUP0_PORTB);  //read portB
		 SIGEV_PULSE_INIT(event, isr_coid_, SIGEV_PULSE_PRIO_INHERIT,
				 BIT_1, port_state);
		break;

	case BIT_3:
		/** if the interrupt is from port C */
		port_state = in8(DIGITAL_CARD_CROUP0_PORTC);  //read portC
		SIGEV_PULSE_INIT(event, isr_coid_, SIGEV_PULSE_PRIO_INHERIT,
				BIT_3, port_state);

		break;

	default:
		break;
	}
	return (event);
}



void HALSensoric::initInterrupt(){

}



void HALSensoric::execute(void *arg){

}


void HALSensoric::shutdown(){

}



