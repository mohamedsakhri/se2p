/*
 * @file 	Reader.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 14, 2012
 *
 * This class represents the reader thread, which reads what is sent to the Serial Interface.
 */

#ifndef READER_H_
#define READER_H_

#include "HAWThread.h"
#include "stdint.h"
#include "Constants.h"
#include "Demultiplexer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace thread;

class Reader: public HAWThread {
public:
	Reader();
	virtual ~Reader();
	virtual void execute(void*arg);
	virtual void shutdown();

private:
	int ser_Interface_id_;		//!< Serial Interface Id
};

#endif /* READER_H_ */
