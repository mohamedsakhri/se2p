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

	coid_ = ConnectAttach(0, 0, chid_, _NTO_SIDE_CHANNEL, 0);
	if (coid_ == -1) {
		perror("ConnectAttach error : ");
	}

	SIGEV_PULSE_INIT(&event_, coid_, SIGEV_PULSE_PRIO_INHERIT, NULL, NULL );

	if(timer_create(CLOCK_REALTIME, &this->event_, &this->timer_id_) == -1) {
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
Timer::Timer(int TimeS, int TimeNS, int chid, int pulseCode, int message)
{
#ifdef DEBUG_
	cout << "Timer :: Constructor" << endl;
#endif
		this->chid_ = chid;

		coid_ = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
		if(coid_ == -1 ){
			perror ("ConnectAttach error : ");
		}

		SIGEV_PULSE_INIT(&event_, coid_, SIGEV_PULSE_PRIO_INHERIT, pulseCode, message );

		if(timer_create(CLOCK_REALTIME, &this->event_, &this->timer_id_) == -1) {
			perror("Timer create error : ");
		}

		this->WaitTimeS_ = TimeS;
	    this->WaitTimeNS_ = TimeNS;
	    this->itime.it_value.tv_sec = this->WaitTimeS_;  			/* 500 million nsecs = .5 secs */
	    this->itime.it_value.tv_nsec = this->WaitTimeNS_;
		this->itime.it_interval.tv_sec = 0;		/* 500 million nsecs = .5 secs */
		this->itime.it_interval.tv_nsec = 0;
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
 *
 */
void Timer::start()
{
#ifdef DEBUG_
	cout << "Timer Start - Timer Id:" << (int)timer_id_ << endl;
	cout << "Timer Value:" <<itime.it_value.tv_sec << endl;
#endif

	if (timer_settime(timer_id_, 0, &itime, NULL) == -1 ) {
		perror("Timer start  error : ");
	}
#ifdef DEBUG_
	cout << "Timer end " << (int)timer_id_ << endl;
#endif

}

/*
 *
 */
void Timer::stop()
{
#ifdef DEBUG_
	cout << "Timer stop - Timer Id:" << (int)timer_id_ << endl;
	cout << "Timer Value:" <<itime.it_value.tv_sec << endl;
#endif

	if (timer_settime(this->timer_id_, 0, NULL, NULL) == -1 ) {
		perror("Timer stop error : ");
	}
}

/*
 *
 */
void Timer::pause()
{
#ifdef DEBUG_
	cout << "Timer pause - Timer Id:" << (int)timer_id_ << endl;
#endif

	if (timer_settime(this->timer_id_, 0, NULL, &remainingTime_) == -1 ) {
		perror("Timer start  error : ");
	}
}

/*
 *
 */
void Timer::resume()
{
#ifdef DEBUG_
	cout << "Timer resume - Timer Id:" << (int)timer_id_ << endl;
#endif

	if (timer_settime(this->timer_id_, 0, &remainingTime_, NULL) == -1 ) {
		perror("Timer start  error : ");
	}
}

///*
// *
// */
//int Timer::getRemainingTime()
//{
//	itimerspec* its ;
//	time_t remaining;
//	timer_gettime(this->timer_id_, its);
//	remaining = its->it_value.tv_sec;
//	return (int) remaining;
//
//}
