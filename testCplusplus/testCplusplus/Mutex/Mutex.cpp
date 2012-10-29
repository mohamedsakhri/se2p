/*
 * Mutex.cpp
 *
 *  Created on: Oct 27, 2012
 *      Author: simohamed
 */

#include "Mutex.h"

Mutex::Mutex() {
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&mutex_, NULL);
}

Mutex::~Mutex() {
	// TODO Auto-generated destructor stub
	pthread_mutex_unlock(&mutex_);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&mutex_);
}



void Mutex::lock()
{
	pthread_mutex_lock(&mutex_);
}


