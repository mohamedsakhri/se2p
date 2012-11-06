/**
 * @file 	PortC.h
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	NOV 2, 2012
 *
 *
 *This class implements all methods needed to interact Port C.
 */
#ifndef PORTC_H_
#define PORTC_H_

#include "Adress.h"
#include "stdint.h"
#include "Mutex.h"

class PortC {
public:
	PortC();	//!< Constructor
	virtual ~PortC();	//!< Destructor
	/**
	 * @param bitNumber Bit's mask to set on
	 */
	void set_Bit_on(uint8_t bitNumber);	//!< Set a bit on
	/**
	 * @param bitNumber Bit's mask to set off
	 */
	void set_Bit_off(uint8_t bitNumber);	//!< Set a bit off

	void Start_LED_on();	//!< Turn Start-LED on
	void Start_LED_off();	//!< Turn Start-LED off
	void Reset_LED_on();	//!< Turn Reset-LED on
	void Reset_LED_off();	//!< Turn Reset-LED off
	void Q1_LED_on();		//!< Turn Q1-LED on
	void Q1_LED_off();		//!< Turn Q1-LED off
	void Q2_LED_on();		//!< Turn Q2-LED on
	void Q2_LED_off();		//!< Turn Q2-LED off


private:
	static Mutex *portC_mutex_;		//!< Mutex for thread-safe implementation
};

#endif /* PORTC_H_ */
