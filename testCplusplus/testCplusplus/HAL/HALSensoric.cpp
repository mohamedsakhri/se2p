/*
 * HALSensoric.cpp
 *
 *  Created on: 07.11.2012
 *      Author: aax877
 */

#include "HALSensoric.h"

#include "HALAktorik.h"

Mutex HALSensoric::hal_Sensoric_mutex_ = Mutex();
HALSensoric* HALSensoric::hal_Sensoric_instance_ = NULL;

static int isr_coid_;


HALSensoric::HALSensoric() {
	// TODO Auto-generated constructor stub
	initInterrupt();

}

HALSensoric::~HALSensoric() {
	// TODO Auto-generated destructor stub
//	delete hal_Sensoric_instance_;
}

HALSensoric *HALSensoric::getInstance() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
			perror("ThreadCtl access failed\n");
			return NULL;
		}
	if (!hal_Sensoric_instance_) {
		hal_Sensoric_mutex_.lock();
		if (!hal_Sensoric_instance_) {
			hal_Sensoric_instance_ = new HALSensoric;
		}
		hal_Sensoric_mutex_.unlock();
	}

	return hal_Sensoric_instance_;
}

const struct sigevent *ISR(void *arg, int id) {

	uint8_t reg_stat;
	uint8_t port_state;
	struct sigevent *event_ = (struct sigevent *) arg;

	/**
	 * read the interrupt register status
	 */
	reg_stat = in8(INTERRUPT_STATUS_REG) & (BIT_1 | BIT_3);
	out8(INTERRUPT_STATUS_REG, 0); // reset interr_register
	// if no interrupt from portC or portB ignore
	if (!reg_stat) {
		return (NULL);
	}

	switch (reg_stat) {
	case BIT_1:
		/** if the interrupt is from port B */
		port_state = in8(DIGITAL_CARD_CROUP0_PORTB); //read portB
		SIGEV_PULSE_INIT(event_, isr_coid_, SIGEV_PULSE_PRIO_INHERIT,
				BIT_1, port_state);
		break;

	case BIT_3:
		/** if the interrupt is from port C */
		port_state = in8(DIGITAL_CARD_CROUP0_PORTC); //read portC
		SIGEV_PULSE_INIT(event_, isr_coid_, SIGEV_PULSE_PRIO_INHERIT,
				BIT_3, port_state);

		break;

	default:
		break;
	}
	return (event_);
}

void HALSensoric::initInterrupt() {
	/*
	 * Create a channel and assign its id to channel_id_
	 * @param 0 Channel with default parameters
	 */
	channel_id_ = ChannelCreate(0);
	if(channel_id_ == -1) {
		perror ("HALSensoric: ChannelCreat failed : ");
		exit(EXIT_FAILURE);
	}
	/*
	 * @param 0 local node
	 * @param 0 channel in the same process, which started the thread
	 * @param channel_id channel id
	 * @param _NTO_SIDE_CHANNEL file descriptor vs. connectionIds
	 * @param 0 default flags
	 */
	isr_coid_ = ConnectAttach(0, 0, channel_id_, _NTO_SIDE_CHANNEL, 0);
	if(isr_coid_ == -1) {
		perror ("HALSensoric: ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
	// Init pulse
	SIGEV_PULSE_INIT(&event_, isr_coid_, SIGEV_PULSE_PRIO_INHERIT,0, 0);
	// 11 : Bit2 in board status register. It reflects the global interrupt.
	// See AIO-Manual p. 16 !?

	interrupt_id_ = InterruptAttach(11, ISR, &event_, sizeof(event_), 0);

	if(interrupt_id_ == -1) {
		perror ("HALSensoric: InterruptAttach failed : ");
		exit(EXIT_FAILURE);
	}

	// Interrupt's configuration
	// reset IRQ status' register
	out8(INTERRUPT_STATUS_REG, 0);
	// Disable interrupts for all ports
	uint8_t intr_ctr = in8(INTERRUPT_CTR_REG);
	out8(INTERRUPT_CTR_REG, intr_ctr | 0x3F);
	// Enable interrupts for port B and Port C low
	intr_ctr = in8(INTERRUPT_CTR_REG);
	out8(INTERRUPT_CTR_REG, intr_ctr & ~(PB_CTR | PC_LOW_CTR));

    // read out port B and C values
    portB_state_ = in8(DIGITAL_CARD_CROUP0_PORTB );
    portC_state_ = in8(DIGITAL_CARD_CROUP0_PORTC);

}

void HALSensoric::execute(void *arg) {
	struct _pulse pulse;


	while( !isStopped()) {
        if( -1 == MsgReceivePulse(channel_id_, &pulse, sizeof(pulse), NULL) ){
            if (isStopped()) {
                break; // channel destroyed, Thread ending
            }
            perror("HALSensoric: MsgReceivePulse");
            exit(EXIT_FAILURE);
        }

//      //  portB_state_ = in8(DIGITAL_CARD_CROUP0_PORTB );
//        //portC_state_ = in8(DIGITAL_CARD_CROUP0_PORTC);
//        cout <<"portB : " << hex << (int) portB_state_ << endl;
//  //      cout <<"portC : " << hex << (int) portC_state_ << endl;

       // cout << " port : " << hex << (int) pulse.code << " Value : " << pulse.value.sival_int << endl;
/*
 *  JUST FOR TEST
 */
        switch(pulse.value.sival_int) {
        case 0xCA:
        	HALAktorik::getInstance()->motor_on();
        	break;
        case 0x4B:
        	HALAktorik::getInstance()->motor_off();
        	break;
        case 0xC3:
        	HALAktorik::getInstance()->open_Switch();
        	break;
        default :
            cout << " Default - port : " << hex << (int) pulse.code << " Value : " << pulse.value.sival_int << endl;

        }
        // just for test

	}
}

void HALSensoric::shutdown() {

}

