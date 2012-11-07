/**
 * @file 	HALAktorik.h
 * @author	Mahmud Dariti
 * @author	Mohamed Sakhri
 * @date	Oct 18, 2012
 *
 * This class implements all methods needed to interact with output-hardware.
 *
 */

#ifndef HALAktorik_H_
#define HALAktorik_H_

#include "HWaccess.h"
#include "Adress.h"
#include "Mutex.h"
#include "PortC.h"
#include "PortA.h"

class HALAktorik {
public:

	virtual ~HALAktorik();	//!< Destructor
	/**
	 * @return instance of HALAktorik
	 */
	static HALAktorik* getInstance();	//!< Used to implement Singleton Pattern

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

	void Start_LED_on();	//!< Turn Start-LED on
	void Start_LED_off();	//!< Turn Start-LED off
	void Reset_LED_on();	//!< Turn Reset-LED on
	void Reset_LED_off();	//!< Turn Reset-LED off
	void Q1_LED_on();		//!< Turn Q1-LED on
	void Q1_LED_off();		//!< Turn Q1-LED off
	void Q2_LED_on();		//!< Turn Q2-LED on
	void Q2_LED_off();		//!< Turn Q2-LED off

private:
	HALAktorik(); //!< Constructor has to be private for the singleton pattern implementation
	PortA *portA_; //!< Represent Port A
	PortC *portC_; //!< Represent Port C
	static HALAktorik *hal_Aktorik_instance_; //!< The only instance of HAL
	static Mutex hal_Aktorik_mutex_; //!< Mutex for thread-safe implementation
};

#endif /* HALAktorik_H_ */
