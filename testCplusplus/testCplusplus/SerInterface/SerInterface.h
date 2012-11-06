/*
 * SerInterface.h
 *
 *  Created on: Oct 27, 2012
 *      Author: simohamed
 */

#ifndef SERINTERFACE_H_
#define SERINTERFACE_H_
#include <termios.h>
#include "Sender.h"
#include "Reader.h"

#define DEVICE "/dev/ser1"
#define TIME_TO_WAIT 20000

class SerInterface {
public:
	SerInterface();
	virtual ~SerInterface();

	//TODO
	/*
	 private :


	 struct termios options;
	 void init();

	 Sender send_thread;
	 Reader read_thread;
	 */

};

#endif /* SERINTERFACE_H_ */
