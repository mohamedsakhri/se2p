/*
 * @file	Timer.cpp
 *
 * @author	Martin Hepke
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
 *
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

	if(timer_create(CLOCK_REALTIME, &event_, &timer_id_) == -1) {
		perror("Timer create error : ");
	}

	//TODO
	this->itime.it_value.tv_sec = 2; /* 500 million nsecs = .5 secs */
	this->itime.it_value.tv_nsec = 50000000;
	this->itime.it_interval.tv_sec = 2; /* 500 million nsecs = .5 secs */
	this->itime.it_interval.tv_nsec = 0;
}

/*
 *
 */
Timer::Timer(int timeS, int timeNS, int chid, int pulseCode, int message)
{
	name_ = -1 ;  			// for debugging (-1 : no given name)
#ifdef DEBUG_
	cout << "Timer :: Constructor" << endl;
#endif
		this->chid_ = chid;

		coid_ = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
		if(coid_ == -1 ){
			perror ("ConnectAttach error : ");
		}
#ifdef DEBUG_
	cout << "Timer :: ConnectAttach" << endl;
#endif
		SIGEV_PULSE_INIT(&event_, coid_, SIGEV_PULSE_PRIO_INHERIT, pulseCode, message );
#ifdef DEBUG_
	cout << "Timer :: SIGEV_PULSE_INIT" << endl;
#endif
		if(timer_create(CLOCK_REALTIME, &event_, &timer_id_) == -1) {
			perror("Timer create error : ");
		}
#ifdef DEBUG_
	cout << "Timer :: timer_create" << endl;
#endif
		this->WaitTimeS_ = timeS;
	    this->WaitTimeNS_ = timeNS;
	    this->itime.it_value.tv_sec = this->WaitTimeS_;  			/* 500 million nsecs = .5 secs */
	    this->itime.it_value.tv_nsec = this->WaitTimeNS_;
		this->itime.it_interval.tv_sec = 0;		/* 500 million nsecs = .5 secs */
		this->itime.it_interval.tv_nsec = 0;
#ifdef DEBUG_
	cout << "Timer :: constructor end" << endl;
#endif
}

/*
 * Detach from channel and delete timer
 */
Timer::~Timer()
{
	if (ConnectDetach(this->event_.sigev_coid == -1)) {
		perror("ConnectDetach error : ");
	}
	if (timer_delete(timer_id_) == -1 ) {
		perror("Timer delete error : ");
	}
}

int Timer::getChId()
{
	return this->chid_;
}

int Timer::getRcvId()
{
	return this->rcvid_;
}

/*
 * Set a new delay for Timer. Because every segment has a different delay
 */
void Timer::setNewTime(int timeS, int timeNS){
	this->WaitTimeS_ = timeS;
    this->WaitTimeNS_ = timeNS;
    this->itime.it_value.tv_sec = this->WaitTimeS_;
    this->itime.it_value.tv_nsec = this->WaitTimeNS_;
}

/*
 *
 */
void Timer::start()
{
#ifdef DEBUG_
	cout << "Timer Start - Timer Id:" << name_ << endl;
	cout << "Timer Value:" <<itime.it_value.tv_sec << endl;
#endif

	if (timer_settime(timer_id_, 0, &itime, NULL) == -1 ) {
		perror("Timer start  error : ");
	}


}

/*
 *
 */
void Timer::stop() {
#ifdef DEBUG_
	cout << "Timer stop - Timer Id:" << name_ << endl;
	cout << "Timer Value:" << itime.it_value.tv_sec << endl;
#endif
	this->itime.it_value.tv_sec = 0;
	this->itime.it_value.tv_nsec = 0;
	if (timer_settime(timer_id_, 0, &itime, NULL) == -1) {
		perror("Timer stop error : ");
	}
}

/*
 *
 */
void Timer::pause()
{
#ifdef DEBUG_
	cout << "Timer pause - Timer Id:" << name_ << endl;
#endif
	this->itime.it_value.tv_sec = 0;
	this->itime.it_value.tv_nsec = 0;
	if (timer_settime(this->timer_id_, 0, &itime, &remainingTime_) == -1 ) {
		perror("Timer pause error : ");
	}
}

/*
 *
 */
void Timer::resume()
{
#ifdef DEBUG_
	cout << "Timer resume - Timer Id:" << name_ << endl;
#endif

	if (timer_settime(this->timer_id_, 0, &remainingTime_, NULL) == -1 ) {
		perror("Timer resume  error : ");
	}
}


/*
 * function for debugging
 */
void Timer::setName(int name)
{
	name_ = name;
}

void Timer::printName()
{
	cout << "Timer name: " << name_ << endl;
}

