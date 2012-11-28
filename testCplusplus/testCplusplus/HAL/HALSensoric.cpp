/**
 * @file 	HALSensoric.cpp
 * @author	Mahmud Dariti
 * @author	Mohamed Sakhri
 * @date	Nov 07, 2012
 *
 * This class implements all methods needed to interact with input-hardware.
 *
 */
//#define DEBUG_
#include "HALSensoric.h"
#include "HALAktorik.h"

Mutex HALSensoric::hal_Sensoric_mutex_ = Mutex();
HALSensoric* HALSensoric::hal_Sensoric_instance_ = NULL;

/**
 * ISR connection id
 */
static int isr_coid_;

/**
 * ISR : Interrupt service routine determines what to do
 * 		when an interrupt occurs
 * @param *arg
 * @param id
 * @return struct sigevent*
 */
const struct sigevent *ISR(void *arg, int id) {

	uint16_t iir;	//!< Interrupt identification register
	uint16_t port_state;	//!< To save Port B and C state temporary
	struct sigevent *event_ = (struct sigevent *) arg;		//<!

	/*
	 * read IRQ register and clear interrupt register at the same time
	 */
//	 iir = in8(READ_IRQ_CLEAR_INTERRUPT) & (BIT_1 | BIT_3);
	 iir = in8(INTERRUPT_STATUS_REG) & (BIT_1 | BIT_3);

	// reset interrupt register
	out8(INTERRUPT_STATUS_REG, 0);
	// if no interrupt or source isn't portC or portB it will be ignored
	if (!iir) {
		return (NULL);
	}

	/* if the interrupt is from port B or C */
	port_state = (in8(DIGITAL_CARD_CROUP0_PORTB) << 8) | (in8(DIGITAL_CARD_CROUP0_PORTC)) ; //read portB and portC
	SIGEV_PULSE_INIT(event_, isr_coid_, SIGEV_PULSE_PRIO_INHERIT,
			IIR_PORTB, port_state);

	return event_;
}

/**
 * Call Interrupt's initializer routine
 */
HALSensoric::HALSensoric() {
	initInterrupt();
}

/**
 * Free memory allocated by HALSensoric instance
 * destroy own channel
 * and detach interrupt
 */
HALSensoric::~HALSensoric() {
	delete hal_Sensoric_instance_;
	ChannelDestroy(channel_id_);
	InterruptDetach(interrupt_id_);
}

/**
 *
 */
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
 * Initialize interrupt's options
 * Called once in constructor
 */
void HALSensoric::initInterrupt() {
#ifdef DEBUG_
	cout << " initInterrupt started ... " << endl;
#endif
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

	// IRQ = 11 : Bit2 in board status register. It reflects the global interrupt.
	// See AIO-Manual p. 16 !?
	interrupt_id_ = InterruptAttach(IRQ, ISR, &event_, sizeof(event_), 0);

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

}

/**
 * Return Workpiece's height after A/D conversion
 */
int HALSensoric::calculateHeight() {
#ifdef DEBUG_
	cout << " calculateHeight started ... " << endl;
#endif
	int height = -1; 	// height to be returned
	int byte_2 = -1;	// value of base + 2h. See AIO manual
	int byte_3 = -1;	// value of base + 3h

	// write control byte to ADC. Range 0-10V supported
	out8(A_IOBASE + BIT_1, AIO_CONVERT_CONTROL);

	// wait till Bit 7 in Base address goes high.
	int i = 1;
	while (true) {
		cout << " i : " << i++ << endl;
		if (in8(A_IOBASE) & BIT_7) {
			// Result can be read as 16bit from Base + 2h. See AIO M. p. 20
			byte_2 = in8(A_IOBASE + 0x02);
			byte_3 = in8(A_IOBASE + 0x03);
			height = (byte_2 << 8) | byte_3;
			break;
		}
	};

//	cout << " calculating : " << height << endl;
	return height;
}

/**
 * Return channel id of Hal Sensoric. That's the only way other classes could get the channel id
 * because as parameter it's private
 */
int HALSensoric::getChannelId() {
	return channel_id_;
}

