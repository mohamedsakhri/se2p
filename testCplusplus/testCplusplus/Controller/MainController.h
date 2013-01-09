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

#ifndef	MAINCONTROLLER_H_
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
	void outSlide();


	int sendMsg2Dispatcher(int message);

	void init();
	void passWP2Ctr();

	void pauseAllTimers();
	void resumeAllTimers();
	void pauseTimers(HALCallInterface* ctr);
	void resumeTimers(HALCallInterface* ctr);

	virtual ~MainController();

private:
	MainController();

	static MainController *mainController_instance_ ;
	static Mutex mainController_mutex_; 		//!< Mutex for thread-safe implementation
};

#endif /* MAINCONTROLLER_H_ */
