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
	 * @param timeS
	 * @param timeNS
	 * @param chid_
	 * @param pulsecode
	 */
	Timer(int timeS, int timeNS, int chid, int pulsecode, int message);

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
	 * @return
	 */
	int getChId();
	/**
	 * @return
	 */
	int getRcvId();
	/**
	 * @return
	 */
	int getRemainingTime();

	virtual ~Timer();

private:
		int WaitTimeS_;
		int WaitTimeNS_;
		struct sigevent			event_;
		struct itimerspec      itime;
		struct itimerspec		remainingTime_;
		timer_t                 timer_id_;
		int						chid_;
		int						coid_;
		int						rcvid_;
};

#endif /* TIMER_H_ */
