/*
 * Sender.h
 *
 *  Created on
 *      Author: simohamed
 */

#ifndef SENDER_H_
#define SENDER_H_

#include "HAWThread.h"

using namespace thread;

class Sender: public HAWThread {
public:
	Sender();
	virtual ~Sender();
	virtual void execute(void*arg);
	virtual void shutdown();
private:
	int ser_Interface_id_;
};

#endif /* SENDER_H_ */
