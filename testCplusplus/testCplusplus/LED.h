/*
 * LED.h
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#ifndef LED_H_
#define LED_H_

#include "Adress.h"
#include "HWaccess.h"

class LED {
public:
	LED();
	virtual ~LED();
private:
	void flashStartLED();
	void darkStartLED();
	void flashResetLED();
	void darkResetLED();
	void flashQ1LED();
	void darkQ1LED();
	void flashQ2LED();
	void darkQ2LED();
};

#endif /* LED_H_ */
