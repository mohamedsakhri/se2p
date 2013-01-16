/*
 * @file	MainController.h
 *
 * @author	Mohamed Sakhri
 * @author	Mahmoud Dariti
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
	void EStopPressedOther();
	void EStopReleasedOther();
	void isMissing();
	void isStranger();
	void slideFull();
	void notTurned();

	//To fix remediable errors
	void slideEmpty();

	/*
	 * @param message Message to be sent.
	 */
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

	/**
	 * @return true if error has been registered
	 */
	bool isErrorRegistered() {
		return errorRegistered_;
	}

	/**
	 * @param errorStatus If error registered or not
	 */
	void setErrorRegistered(bool errorStatus) {
		errorRegistered_ = errorStatus;
	}

	/**
	 * @return true if error has been registered
	 */
	bool isM2Ready() {
		return isM2Ready_;
	}

	/**
	 * @param errorStatus If error registered or not
	 */
	void setM2Ready(bool m2Ready) {
		errorRegistered_ = m2Ready;
	}

	/**
	 * Set machine2's status to busy
	 */
	void m2isBusy() {
		isM2Ready_ = false;
	}

	/**
	 * Set machine2's status to busy
	 */
	void m2isReady() {
		isM2Ready_ = true;
	}

	virtual ~MainController();

private:
	MainController();

	bool errorRegistered_;						//!< Error's registration state
	bool isM2Ready_;							//!< Machine's state

	static MainController *mainController_instance_ ;
	static Mutex mainController_mutex_; 		//!< Mutex for thread-safe implementation
};

#endif /* MAINCONTROLLER_H_ */
