/*
 * @file 	Mutex.cpp
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date	Oct 27, 2012
 *
 * This class implements an own Mutex based on POSIX's mutex
 */

#include "Mutex.h"

/**
 * Initialize the Mutex
 */
Mutex::Mutex() {
	pthread_mutex_init(&mutex_, NULL);
}

/**
 * Destroy the Mutex
 */
Mutex::~Mutex() {
	pthread_mutex_destroy(&mutex_);
}

/**
 * Lock the Mutex
 */

void Mutex::unlock() {
	pthread_mutex_unlock(&mutex_);
}

/**
 * Unlock the Mutex
 */

void Mutex::lock() {
	pthread_mutex_lock(&mutex_);
}

