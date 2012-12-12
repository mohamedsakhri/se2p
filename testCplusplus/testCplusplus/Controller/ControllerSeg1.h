/*
 * @file 	ControllerSeg1.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Nov 26, 2012
 *
 * This class represents the controller of the first segment.
 */

#ifndef CONTROLLERSEG1_H_
#define CONTROLLERSEG1_H_

#include "HALCallInterface.h"
#include "SegLineStart.h"
#include "ControllerSeg2.h"


class ControllerSeg1: public HALCallInterface {
public:
	static ControllerSeg1* getInstance();

	void inLineStart();
	void outLineStart();
	void startPressed();
	void stopPressed();
	void EStopPressed();
	void EStopReleased();

	// Error's handling
	int sendMsg2Dispatcher(int message);

	void init();
	void passWP2Ctr();

	virtual ~ControllerSeg1();

private:
	ControllerSeg1();

	static ControllerSeg1 *controllerSeg1_instance_ ;
	static Mutex controllerSeg1_mutex_; 		//!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEG1_H_ */
