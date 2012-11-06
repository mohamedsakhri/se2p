/*
 * Mutex.h
 *
 *  Created on: Oct 27, 2012
 *      Author: simohamed
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include "pthread.h"

class Mutex {
public:
	Mutex();
	virtual ~Mutex();
	void lock();
	void unlock();

private:
	pthread_mutex_t mutex_;
};

#endif /* MUTEX_H_ */
