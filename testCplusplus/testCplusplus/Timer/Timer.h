/*
 * @file	Timer.h
 *
 * @author	Martin Hepke
 *
 * @date	 Dec 14, 2012
 *
 * This class implements the Software timer
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdio.h>
#include <time.h>
#include <sys/netmgr.h>
#include <sys/neutrino.h>

#define MY_PULSE_CODE   _PULSE_CODE_MINAVAIL
#define MY_PULSE_COD2   _PULSE_CODE_MAXAVAIL

class Timer {
public:
	Timer();
	/**
	 * @param timeS 	Time in seconds
	 * @param timeNS 	Time in nanoseconds
	 * @param chid 		Channel-Id to which message will be send
	 * @param pulsecode Pulse's code
	 * @param message 	Message to be sent when timer fires
	 */
	Timer(int timeS, int timeNS, int chid, int pulsecode, int message);

	/*
	 * Methods to control timer
	 */
	void start();
	void pause();
	void resume();
	void stop();

	/**
	 * @param timeS Time in seconds
	 * @param timeNS Time in nanoseconds
	 */
	void setNewTime(int timeS,int timeNS);

	/**
	 * @return Channel-Id
	 */
	int getChId();

	/**
	 * @return Rmaining time for timer to fire
	 */
	int getRemainingTime();

	/*
	 * Methods for debugging only
	 * @param name : Timer Id
	 */
	void setName(int name);
	void printName();

	virtual ~Timer();

private:
		struct sigevent			event_;			//!< Event to be sent when timer fires
		struct itimerspec      itime;			//!< Timer's time
		struct itimerspec		remainingTime_;	//!< Remaining time for timer to fire
		timer_t                 timer_id_;		//!< Timer to be created
		int						chid_;			//!< Channel-Id
		int						coid_;			//!< Connection-Id
		// For debug only
		int 					name_;			// Timer-Id
};

#endif /* TIMER_H_ */
