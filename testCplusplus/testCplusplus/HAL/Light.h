/*
 * Light.h
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#ifndef LIGHT_H_
#define LIGHT_H_
#include "HWaccess.h"
#include "Adress.h"
#include "stdint.h"

class Light {
public:
	Light();
	virtual ~Light();

	void light_on(uint8_t bitNumber);
	void light_off(uint8_t bitNUmber);

	void green_Light_on();
	void green_Light_off();
	void yellow_Light_on();
	void yellow_Light_off();
	void red_Light_on();
	void red_Light_off();
	void red_Light_slow();
	void red_Light_quick();
};

#endif /* LIGHT_H_ */
