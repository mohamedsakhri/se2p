/**
 * @file 	PortC.cpp
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	NOV 2, 2012
 *
 */
#include "PortC.h"
#include "HWaccess.h"
#include <iostream.h>

/**
 * Mutex locks and unlocks access to Port C to assure thread-safe implementation.
 *
 * \see set_Bit_on()
 * \see set_Bit_off()
 */
Mutex* PortC::portC_mutex_ = new Mutex();

/**
 * Constructor does nothing
 */
PortC::PortC() {
}

/**
 * Destructor does nothing
 */
PortC::~PortC() {
}

/**
 * This method takes the bit's mask which has to be set on as parameter and it's thread-safe.
 * \see portC_mutex
 */
void PortC::set_Bit_on(uint8_t bitNumber) {
	portC_mutex_->lock();
#ifdef DEBUG_MUTEX
	cout << "On:PortC_Mutex locked" << endl;
#endif
	uint8_t portC_state = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, portC_state | bitNumber);
	portC_mutex_->unlock();
#ifdef DEBUG_MUTEX
	cout << "On:PortC_Mutex locked" << endl;
#endif
}

/**
 * This method takes the bit's mask which has to be set off as parameter and it's thread-safe.
 * \see portC_mutex
 */
void PortC::set_Bit_off(uint8_t bitNumber) {
	portC_mutex_->lock();
#ifdef DEBUG_MUTEX
	cout << "Off:PortC_Mutex locked" << endl;
#endif
	uint8_t portC_state = in8(DIGITAL_CARD_CROUP0_PORTC);
	out8(DIGITAL_CARD_CROUP0_PORTC, ~bitNumber & portC_state);
	portC_mutex_->unlock();
#ifdef DEBUG_MUTEX
	cout << "Off:PortC_Mutex locked" << endl;
#endif
}

/************************************************************************************
 *									LEDs											*
 *																					*
 ************************************************************************************/

/**
 * \see set_Bit_on()
 */
void PortC::Start_LED_on() {
	PortC::set_Bit_on(BIT_0);
}

/**
 * \see set_Bit_off()
 */
void PortC::Start_LED_off() {
	PortC::set_Bit_off(BIT_0);
}

/**
 * \see set_Bit_on()
 */
void PortC::Reset_LED_on() {
	PortC::set_Bit_on(BIT_1);
}

/**
 * \see set_Bit_off()
 */
void PortC::Reset_LED_off() {
	PortC::set_Bit_off(BIT_1);
}

/**
 * \see set_Bit_on()
 */
void PortC::Q1_LED_on() {
	PortC::set_Bit_on(BIT_2);
}

/**
 * \see set_Bit_off()
 */
void PortC::Q1_LED_off() {
	PortC::set_Bit_off(BIT_2);
}

/**
 * \see set_Bit_on()
 */
void PortC::Q2_LED_on() {
	PortC::set_Bit_on(BIT_3);
}

/**
 * \see set_Bit_off()
 */
void PortC::Q2_LED_off() {
	PortC::set_Bit_off(BIT_3);
}
