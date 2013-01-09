/*
 * @file 	ControllerSeg4.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * This class represents the controller of the third segment which controls the slide area
 */

#ifndef CONTROLLERSEG4_H_
#define CONTROLLERSEG4_H_

#include "HALCallInterface.h"
#include "SegSlide.h"

class ControllerSeg4: public HALCallInterface {
public:
	/**
	 * @return The controller's instance
	 */
	static ControllerSeg4* getInstance();

	void inSlide();
	void outSlide();

	// Error's handling
	int sendMsg2Dispatcher(int message);
	void init();
	void passWP2Ctr();

	Timer* getTimer();

	virtual ~ControllerSeg4();

private:
	ControllerSeg4();
	Timer* timer_seg4_;
	static ControllerSeg4* controllerSeg4_instance_;
	static Mutex controllerSeg4_mutex_; //!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEG4_H_ */
