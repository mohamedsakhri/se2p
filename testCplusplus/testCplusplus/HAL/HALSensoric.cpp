/**
 * @file 	HALSensoric.cpp
 * @author	Mahmud Dariti
 * @author	Mohamed Sakhri
 * @date	Nov 07, 2012
 *
 * This class implements all methods needed to interact with input-hardware.
 *
 */
#define DEBUG_
#include "HALSensoric.h"
#include "HALAktorik.h"

Mutex HALSensoric::hal_Sensoric_mutex_ = Mutex();
HALSensoric* HALSensoric::hal_Sensoric_instance_ = NULL;

/**
 * ISR connection id
 */
static int isr_coid_;


HALSensoric::HALSensoric() {
	initInterrupt();

}

HALSensoric::~HALSensoric() {
	delete hal_Sensoric_instance_;
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

/**
 * ISR : Interrupt service routine determines what to do
 * 		when an interrupt occurs
 * @param *arg
 * @param id
 * @return struct sigevent*
 */
const struct sigevent *ISR(void *arg, int id) {
#ifdef DEBUG_
	cout << " ISR started ... " << endl;
#endif
	uint8_t reg_stat;	//!< Interrupt register status
	uint8_t port_state;	//!< To save Port B and c state temporary
	struct sigevent *event_ = (struct sigevent *) arg;		//<!

	/*
	 * read the interrupt register status
	 */
	reg_stat = in8(INTERRUPT_STATUS_REG) & (BIT_1 | BIT_3);
	out8(INTERRUPT_STATUS_REG, 0); // reset interr_register
	// if no interrupt's source isn't portC or portB it will be ignored
	if (!reg_stat) {
		return (NULL);
	}

	/*
	 * determine which port causes the interrupt and react
	 */
	switch (reg_stat) {
	case BIT_1:
		/* if the interrupt is from port B */
		port_state = in8(DIGITAL_CARD_CROUP0_PORTB); //read portB
		SIGEV_PULSE_INIT(event_, isr_coid_, SIGEV_PULSE_PRIO_INHERIT,
				BIT_1, port_state);
		break;

	case BIT_3:
		/* if the interrupt is from port C */
		port_state = in8(DIGITAL_CARD_CROUP0_PORTC); //read portC
		SIGEV_PULSE_INIT(event_, isr_coid_, SIGEV_PULSE_PRIO_INHERIT,
				BIT_3, port_state);
		break;

	default:
		break;
	}
	return (event_);
}

/**
 * Initialize interrupt's options
 * It will be called once in constructor
 */
void HALSensoric::initInterrupt() {
	/*
	 * Create a channel and assign its id to channel_id_
	 * @param 0 Channel with default parameters
	 */
#ifdef DEBUG_
	cout << " initInterrupt started ... " << endl;
#endif
	channel_id_ = ChannelCreate(0);
	if(channel_id_ == -1) {
		perror ("HALSensoric: ChannelCreat failed : ");
		exit(EXIT_FAILURE);
	}
	/*
	 * 	0 : 				local node
	 * 	0 : 				channel in the same process, which started the thread
	 * 	channel_id : 		channel id
	 * 	_NTO_SIDE_CHANNEL : file descriptor vs. connectionIds
	 * 	0 : 				default flags
	 */
	isr_coid_ = ConnectAttach(0, 0, channel_id_, _NTO_SIDE_CHANNEL, 0);
	if(isr_coid_ == -1) {
		perror ("HALSensoric: ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}
	// Initialize pulse
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
int HALSensoric::calculateHeight() {
#ifdef DEBUG_
	cout << " calculateHeight started ... " << endl;
#endif
	int height = 0;
	// write control byte to ADC
	out8(A_IOBASE + BIT_1, AIO_CONVERT_CONTROL);

	// wait til Bit 7 in Base adress goes high => Conversion is done
	while (in8(A_IOBASE) & BIT_7) {};

	// Result can be read as 16bit from Base + 2h. See AIO M. p. 20
	height = in16(A_IOBASE + AD_C_LOW_OFFS);

	return height;
}

/**
 * returns channel id of Hal Sensoric. That's the only way other classes could get the channel id
 * because as parameter it's private
 */
int HALSensoric::getChannelId() {
	return channel_id_;
}
