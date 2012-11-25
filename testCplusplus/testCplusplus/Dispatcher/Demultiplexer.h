/*
 * @file Demultiplexer.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date Nov 25, 2012
 *
 *
 *	This Class implements the Demultiplexer's. It's a part of the Dispatcher's design pattern.
 *	Demultiplexer gets Events from HALsensoric, interprets them and send a message to dispatcher
 *	containing exactly what happened in the engine
 */

#ifndef DEMULTIPLEXER_H_
#define DEMULTIPLEXER_H_

#include "HAWThread.h"
#include "HALSensoric.h"
#include "Dispatcher.h"
#include "Mutex.h"
#include "Messages.h"

using namespace thread;

class Demultiplexer: public HAWThread {
public:
	virtual ~Demultiplexer();
	/**
	 * @return Demupltiplexer's instance
	 */
	static Demultiplexer* getInstance(); 			//!< For Singleton pattern implementation

	/**
	 * @return Demultiplexer's channel ID
	 */
	int getChannelId();							//!< used to get Channel ID from outside this class

	virtual void execute(void* arg);
	virtual void shutdown();

private:
	Demultiplexer();
	int channel_id_;									//!< get Channel ID to receive and send messages
	int con_id_;										//!< Connection ID : with HAL Sensoric
	HALSensoric *hal_sensoric_;
	static Demultiplexer *demultiplexer_instance_;		//!< The only demultiplexer's instance
	static Mutex demultiplexer_mutex_;					//!< Mutex used in Singleton implementation
	Dispatcher *dispatcher_;


};

#endif /* DEMULTIPLEXER_H_ */
