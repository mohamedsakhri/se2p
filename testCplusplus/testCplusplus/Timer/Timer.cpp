/*
 * @file	Timer.cpp
 *
 * @author	Martin Hepke
 * @author 	Mohamed Sakhri
 * @author	Mahmud Dariti
 *
 * @date	 Dec 14, 2012
 *
 * This class implements the Software timer
 */

#include "Timer.h"
#include <iostream>

#define DEBUG_

using namespace std;

/*
 * Constructor for timer with default parameters
 */
Timer::Timer() {
#ifdef DEBUG_
	cout << "Timer :: Constructor" << endl;
#endif

	name_ = -1 ;  			// for debugging (-1 : no given name)

	coid_ = ConnectAttach(0, 0, chid_, _NTO_SIDE_CHANNEL, 0);
	if (coid_ == -1) {
		perror("ConnectAttach error : ");
	}

	SIGEV_PULSE_INIT(&event_, coid_, SIGEV_PULSE_PRIO_INHERIT, NULL, NULL );

	// Create new timer
	if(timer_create(CLOCK_REALTIME, &event_, &timer_id_) == -1) {
		perror("Timer create error : ");
	}
	this->itime.it_value.tv_sec = 2; /* 500 million nsecs = .5 secs */
	this->itime.it_value.tv_nsec = 50000000;
	this->itime.it_interval.tv_sec = 2; /* 500 million nsecs = .5 secs */
	this->itime.it_interval.tv_nsec = 0;
}

/*
 * Constructor for timer with given parameters
 */
Timer::Timer(int timeS, int timeNS, int chid, int pulseCode, int message) {
#ifdef DEBUG_
	cout << "Timer :: Constructor" << endl;
#endif
	// For debugging (-1 : No given name)
	name_ = -1;

	this->chid_ = chid;

	coid_ = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
	if (coid_ == -1) {
		perror("ConnectAttach error : ");
	}

	SIGEV_PULSE_INIT(&event_, coid_, SIGEV_PULSE_PRIO_INHERIT, pulseCode, message );

	if (timer_create(CLOCK_REALTIME, &event_, &timer_id_) == -1) {
		perror("Timer create error : ");
	}

	this->itime.it_value.tv_sec = timeS;
	this->itime.it_value.tv_nsec = timeNS;
	this->itime.it_interval.tv_sec = 0;
	this->itime.it_interval.tv_nsec = 0;
}

/*
 * Return channel-ID to which timer is connected
 */
int Timer::getChId()
{
	return this->chid_;
}

/*
 * Set a new delay for Timer. Because every segment has a different delay
 */
void Timer::setNewTime(int timeS, int timeNS){
#ifdef DEBUG_
	cout << "Timer SetNewTime : " << endl << " ID :	" << name_;
	cout << "Value:	" << timeS << endl;
#endif

    this->itime.it_value.tv_sec = timeS;
    this->itime.it_value.tv_nsec = timeNS;
}

/*
 * Start timer
 */
void Timer::start() {
#ifdef DEBUG_
	cout << "Timer Start : " << endl << " ID :	" << name_;
	cout << "Value:	" << itime.it_value.tv_sec << endl;
#endif

	if (timer_settime(timer_id_, 0, &itime, NULL) == -1) {
		perror("Timer start  error : ");
	}
}

/*
 * Stop timer
 */
void Timer::stop() {
#ifdef DEBUG_
	cout << "Timer Stop : " << endl << " ID :	" << name_;
	cout << "Value:	" << itime.it_value.tv_sec << endl;
#endif

	this->itime.it_value.tv_sec = 0;
	this->itime.it_value.tv_nsec = 0;
	if (timer_settime(timer_id_, 0, &itime, NULL) == -1) {
		perror("Timer stop error : ");
	}
}

/*
 * Pause timer
 */
void Timer::pause() {
#ifdef DEBUG_
	cout << "Timer Pause : " << endl << " ID :	" << name_;
	cout << "Value:	" << itime.it_value.tv_sec << endl;
#endif

	this->itime.it_value.tv_sec = 0;
	this->itime.it_value.tv_nsec = 0;
	if (timer_settime(this->timer_id_, 0, &itime, &remainingTime_) == -1) {
		perror("Timer pause error : ");
	}
}

/*
 * Resume Timer
 */
void Timer::resume() {
#ifdef DEBUG_
	cout << "Timer Resume : " << endl << " ID :	" << name_;
	cout << "Value:	" << itime.it_value.tv_sec << endl;
#endif

	if (timer_settime(this->timer_id_, 0, &remainingTime_, NULL) == -1) {
		perror("Timer resume  error : ");
	}
}


/*
 * For debugging only : Give each timer an ID
 */
void Timer::setName(int name)
{
	name_ = name;
}

/*
 * For debugging only : Print timer ID
 */
void Timer::printName()
{
	cout << "Timer name: " << name_ << endl;
}

/*
 * Detach from channel and delete timer
 */
Timer::~Timer()
{
#ifdef DEBUG_
	cout << "Timer Deconstructor : " << endl << " ID :	" << name_;
#endif

	if (ConnectDetach(this->event_.sigev_coid == -1)) {
		perror("ConnectDetach error : ");
	}
	if (timer_delete(timer_id_) == -1 ) {
		perror("Timer delete error : ");
	}
}

