/*
 * Switch.h
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "Adress.h"
#include "HWaccess.h"

class Switch {
public:
	Switch();
	virtual ~Switch();
private:
	void open();
	void close();
	bool isOpen();
};

#endif /* SWITCH_H_ */
