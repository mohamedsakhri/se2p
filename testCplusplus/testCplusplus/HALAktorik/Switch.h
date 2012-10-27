/*
 * Switch.h
 *
 *  Created on: Oct 25, 2012
 *      Author: simohamed
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "HALAktorik.h"

class Switch {
public:
	Switch();
	virtual ~Switch();

	void open_Switch();
	void close_Switch();
	bool is_Switch_Open();
};

#endif /* SWITCH_H_ */
