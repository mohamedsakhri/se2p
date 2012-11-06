/**
 * @file 	PortA.h
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	NOV 2, 2012
 *
 *
 *This class implements all methodes needed to interact Port A.
 */

#ifndef PORTA_H_
#define PORTA_H_
#include "Adress.h"
#include "stdint.h"
#include "Mutex.h"
#include "Constants.h"

class PortA {
public:
	PortA();	//!< Constructor
	virtual ~PortA();	//!< Destructor
	/**
	 * @param bitNumber Bit's mask to set on
	 */
	void set_Bit_on(uint8_t bitNumber);	//!< Set a bit on
	/**
	 * @param bitNumber Bit's mask to set off
	 */
	void set_Bit_off(uint8_t bitNumber);	//!< Set a bit off

	void green_Light_on();	//!< Turn green light on
	void green_Light_off();	//!< Turn green light off
	void yellow_Light_on();	//!< Turn yellow light on
	void yellow_Light_off();	//!< Turn yellow light off
	void red_Light_on();		//!< Turn red light on
	void red_Light_off();		//!< Turn red light off
	void red_Light_slow();	//!< Start red light flashing slowly
	void red_Light_quick();	//!< Start red light flashing quickly

	void motor_on();	//!< Turn motor on
	void motor_off();	//!< Turn motor off
	void run_slow();	//!< Run production line slowly
	void run_right();	//!< Run production line from right to left
	void run_left();	//!< Run production line from left to right
	void stop_Motor();	//!< Stop motor

	void open_Switch();	//!< Open the switch
	void close_Switch();	//!< Close the switch
	/**
	 * @return true if the switch is open
	 */
	bool is_Switch_Open();	//!<Return the switch's state.


private:
	static Mutex *portA_mutex_;		//!< Mutex for thread-safe implementation
};

#endif /* PORTA_H_ */
