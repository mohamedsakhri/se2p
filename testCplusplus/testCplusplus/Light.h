/*
 * Light.h
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Adress.h"
#include "HWaccess.h"

class Light {
public:
	Light();
	virtual ~Light();
private:
	void lightOn(uint8_t bitNumber);
	void lightOff(uint8_t bitNUmber);
	void greenLightOn();
	void greenLightOff();
	void yellowLightOn();
	void yellowLightOff();
	void redLightOn();
	void redLightOff();
};

#endif /* LIGHT_H_ */
