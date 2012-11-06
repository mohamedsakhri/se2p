/*
 * Reader.h
 *
 *  Created on:
 *      Author: simohamed
 */

#ifndef READER_H_
#define READER_H_

#include "HAWThread.h"

using namespace thread;
class Reader: public HAWThread {
public:
	Reader();
	virtual ~Reader();
	virtual void execute(void*arg);
	virtual void shutdown();
private:
	int ser_Interface_id_;
};

#endif /* READER_H_ */
