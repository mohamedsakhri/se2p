/*
 * Motor.h
 *
 *  Created on: Oct 24, 2012
 *      Author: simohamed
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "Adress.h"
#include "HWaccess.h"

class Motor {
public:
	Motor();
	virtual ~Motor();
private:
	void motorOn();	// will be called at the start, it just calls runRight() or runLeft()
	void motorOff();	// stops the motor by changing BIT_1 or BIT_2
	void runSlow();	// not needed in our Software, but good to have it anyway
	void runRight();	// run right "in normal speed"
	void runLeft();	// not needed neither
	void stopMotor();	// stops the motor by changing BIT_3, not changing BIT_1, BIT_2 or BIT_3
						// could be used to hold the band for a defined time too * just an Idea*
};

#endif /* MOTOR_H_ */
