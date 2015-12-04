/*
 * @file 	Sender.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 14, 2012
 *
 * This class represents the sender. It initialize the Serial Interface
 * and offers a method to send messages.
 *
 */

#include <iostream>
#include "stdint.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Mutex.h"
#include "Constants.h"

#ifndef SENDER_H_
#define SENDER_H_


class Sender{
public:
	virtual ~Sender();
	/**
	 * @return instance The only sender's instance
	 */
	static Sender* getInstance();

	/**
	 * @param message Message to be sent to the Serial Interface
	 */
	virtual void send(int message);

private:
	Sender();

	int ser_Interface_id_;				//!< Serial Interface Id
	static Sender *sender_instance_ ;	//!< Sender's instance
	static Mutex sender_mutex_; 		//!< Mutex for thread-safe implementation
};

#endif /* SENDER_H_ */
