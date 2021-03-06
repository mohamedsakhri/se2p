/*
 * @file 	ControllerSeg3.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * This class represents the controller of the third segment which controls the switch area
 */

#ifndef CONTROLLERSEG3_H_
#define CONTROLLERSEG3_H_

#include "HALCallInterface.h"
#include "SegSwitch.h"
#include "ControllerSeg4.h"
#include "ControllerSeg5.h"


class ControllerSeg3: public HALCallInterface {
public:
	/**
	 * @return The controller's instance
	 */
	static ControllerSeg3* getInstance();

	void inSwitch();
	void outSwitch();

	/**
	 * @param message Message to be sent.
	 */
	int sendMsg2Dispatcher(int message);
	void init();
	void passWP2Ctr();
	/**
	 * @param ctr_id Controller Id
	 */
	void passWP2Ctr(int ctr_id);
	void reset();

	virtual ~ControllerSeg3();

private:
	ControllerSeg3();

	static ControllerSeg3* controllerSeg3_instance_;	//!< Controller's instance
	static Mutex controllerSeg3_mutex_; 				//!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEG3_H_ */
