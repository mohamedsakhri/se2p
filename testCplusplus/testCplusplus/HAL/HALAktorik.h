/*
 * HALAktorik.h
 *
 *  Created on: Oct 18, 2012
 *      Author: simohamed
*/

#ifndef HALAktorik_H_
#define HALAktorik_H_

#include "HWaccess.h"
#include "Adress.h"
#include "Mutex.h"
#include "LED.h"
#include "Switch.h"
#include "Motor.h"
#include "Light.h"


class HALAktorik {
public:
	virtual ~HALAktorik();

	static HALAktorik* getInstance();

	void green_Light_on();
	void green_Light_off();
	void yellow_Light_on();
	void yellow_Light_off();
	void red_Light_on();
	void red_Light_off();

	void red_Light_slow();
	void red_Light_quick();

	void motor_on();	// will be called at the start, it just calls runRight() or runLeft()
	void motor_off();	// stops the motor by changing BIT_1 or BIT_2
	void run_slow();	// not needed in our Software, but good to have it anyway
	void run_right();	// run right "in normal speed"
	void run_left();	// not needed neither
	void stop_Motor();	// stops the motor by changing BIT_3, not changing BIT_1, BIT_2 or BIT_3
						// could be used to hold the band for a defined time too * just an Idea*

	void open_Switch();
	void close_Switch();
	bool is_Switch_Open();

	void Start_LED_on();
	void Start_LED_off();
	void Reset_LED_on();
	void Reset_LED_off();
	void Q1_LED_on();
	void Q1_LED_off();
	void Q2_LED_on();
	void Q2_LED_off();

private :
	HALAktorik();
	LED *led_;
	Light *light_;
	Motor *motor_;
	Switch *switch_;
	static HALAktorik *hal_Aktorik_instance_;
	static Mutex *hal_Aktorik_mutex_;
};

#endif /* HALAktorik_H_ */
