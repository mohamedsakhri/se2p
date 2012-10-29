/*
 * Motor.h
 *
 *  Created on: Oct 24, 2012
 *      Author: simohamed
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include "HWaccess.h"
#include "Adress.h"

class Motor {
public:
	Motor();
	virtual ~Motor();

	void motor_on();	// will be called at the start, it just calls runRight() or runLeft()
	void motor_off();	// stops the motor by changing BIT_1 or BIT_2
	void run_slow();	// not needed in our Software, but good to have it anyway
	void run_right();	// run right "in normal speed"
	void run_left();	// not needed neither
	void stop_Motor();	// stops the motor by changing BIT_3, not changing BIT_1, BIT_2 or BIT_3
						// could be used to hold the band for a defined time too * just an Idea*
};

#endif /* MOTOR_H_ */
