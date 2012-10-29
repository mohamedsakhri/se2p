/*
 * LED.h
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#ifndef LED_H_
#define LED_H_
#include "HWaccess.h"
#include "Adress.h"

class LED {
public:
	LED();
	virtual ~LED();

	void Start_LED_on();
	void Start_LED_off();
	void Reset_LED_on();
	void Reset_LED_off();
	void Q1_LED_on();
	void Q1_LED_off();
	void Q2_LED_on();
	void Q2_LED_off();
};

#endif /* LED_H_ */
