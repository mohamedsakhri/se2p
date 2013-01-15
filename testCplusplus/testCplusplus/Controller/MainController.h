/*
 * @file	MainController.h
 *
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 19, 2012
 *
 * Classes which represent the main controller
 *
 */

#ifndef	 MAINCONTROLLER_H_
#define MAINCONTROLLER_H_

#include "HALCallInterface.h"


class MainController: public HALCallInterface {
public:
	/**
	 * @return The controller's instance
	 */
	static MainController* getInstance();

	void startPressed();
	void stopPressed();
	void resetPressed();
	void resetReleased();
	void EStopPressed();
	void EStopReleased();
	void isMissing();
	void isStranger();
	void slideFull();
	void notTurned();

	//To fix remediable errors
	void slideEmpty();


	int sendMsg2Dispatcher(int message);

	void init();
	void passWP2Ctr();

	/**
	 * Pause all timers
	 */
	void pauseAllTimers();

	/**
	 * Pause a controller's timer
	 * @param ctr Controller which timers has to be paused
	 */
	void pauseTimers(HALCallInterface* ctr);

	/**
	 * Resume all timers
	 */
	void resumeAllTimers();

	/**
	 * Resume a controller's timer
	 * @param ctr Controller which timers has to be resumed
	 */
	void resumeTimers(HALCallInterface* ctr);

	/**
	 * stop all timer
	 */
	void stopAllTimers();

	/**
	 * stop a controller's timer
	 * @param ctr Controller which timers has to be paused
	 */
	void stopTimers(HALCallInterface* ctr);

	bool isEStopPressed() {
		return EStop_pressed_;
	}

	void setEStop(bool estop) {
		EStop_pressed_ = estop;
	}

	virtual ~MainController();

private:
	MainController();
	bool EStop_pressed_ ;
	static MainController *mainController_instance_ ;
	static Mutex mainController_mutex_; 		//!< Mutex for thread-safe implementation
};

#endif /* MAINCONTROLLER_H_ */
