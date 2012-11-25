/**
 * @file 	PortA.cpp
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri *
 * @date	NOV 2, 2012
 *
 *This class implements all methods needed to interact Port A.
 */

#include "PortA.h"
#include "HWaccess.h"
#include <iostream.h>

/**
 * Mutex locks and unlocks access to Port A to assure thread-safe implementation.
 *
 * \see set_Bit_on()
 * \see set_Bit_off()
 */
Mutex PortA::portA_mutex_ = Mutex();

/**
 * Constructor does nothing
 */
PortA::PortA() {
}

/**
 * Destructor does nothing
 */
PortA::~PortA() {

}

/**
 * This method takes the bit's mask which has to be set on as parameter and it's thread-safe.
 * \see portA_mutex
 */
void PortA::set_Bit_on(uint8_t bitNumber) {
	portA_mutex_.lock();
#ifdef DEBUG_MUTEX
	cout << "On:PortA_Mutex locked" << endl;
#endif
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, bitNumber | portAState);
	portA_mutex_.unlock();
#ifdef DEBUG_MUTEX
	cout << "On:PortA_Mutex unlocked" << endl;
#endif
}

/**
 * This method takes the bit's mask which has to be set off as parameter and it's thread-safe.
 * \see portA_mutex
 */
void PortA::set_Bit_off(uint8_t bitNumber) {
	portA_mutex_.lock();
#ifdef DEBUG_MUTEX
	cout << "Off:PortA_Mutex locked" << endl;
#endif
	uint8_t portAState = in8(DIGITAL_CARD_CROUP0_PORTA);
	out8(DIGITAL_CARD_CROUP0_PORTA, ~bitNumber & portAState);
	portA_mutex_.unlock();
#ifdef DEBUG_MUTEX
	cout << "Off:PortA_Mutex unlocked" << endl;
#endif
}

/************************************************************************************
 *									MOTOR											*
 *																					*
 ************************************************************************************/

/**
 * \see set_Bit_on()
 */
void PortA::motor_on() {
	PortA::set_Bit_on(BIT_0);
}

/**
 * \see set_Bit_off()
 */
void PortA::motor_off() {
	PortA::set_Bit_off(BIT_0);
}

/**
 * \see set_Bit_on()
 */
void PortA::run_right() {
	PortA::set_Bit_on(BIT_0);
}

/**
 * \see set_Bit_on()
 */
void PortA::run_left() {
	PortA::set_Bit_on(BIT_1);
}

/**
 * \see set_Bit_on()
 */
void PortA::run_slow() {
	PortA::set_Bit_on(BIT_2);
}

/**
 * \see set_Bit_on()
 */
void PortA::stop_Motor() {
	PortA::set_Bit_on(BIT_3);
}

/************************************************************************************
 *									LIGHTS											*
 *																					*
 ************************************************************************************/

/**
 * \see set_Bit_on()
 */
void PortA::green_Light_on() {
	PortA::set_Bit_on(BIT_5);
}

/**
 * \see set_Bit_off()
 */
void PortA::green_Light_off() {
	PortA::set_Bit_off(BIT_5);
}

/**
 * \see set_Bit_on()
 */
void PortA::yellow_Light_on() {
	PortA::set_Bit_on(BIT_6);
}

/**
 * \see set_Bit_off()
 */
void PortA::yellow_Light_off() {
	PortA::set_Bit_off(BIT_6);
}

/**
 * \see set_Bit_on()
 */
void PortA::red_Light_on() {
	PortA::set_Bit_on(BIT_7);
}

/**
 * \see set_Bit_off()
 */
void PortA::red_Light_off() {
	PortA::set_Bit_off(BIT_7);
}


/************************************************************************************
 *									SWITCH											*
 *																					*
 ************************************************************************************/

bool PortA::is_Switch_Open() {
	return (in8(DIGITAL_CARD_CROUP0_PORTA) | BIT_4);
}

/**
 * \see set_Bit_on()
 */
void PortA::open_Switch() {
	PortA::set_Bit_on(BIT_4);
}

/**
 * \see set_Bit_off()
 */
void PortA::close_Switch() {
	PortA::set_Bit_off(BIT_4);
}
