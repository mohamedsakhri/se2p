/*
 * @file 	Mutex.h
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date	Oct 27, 2012
 *
 * This class implements an own Mutex based on POSIX's mutex
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
