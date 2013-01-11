/*
 * @file 	ControllerSeg2.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * This class represents the controller of the first segment which controls the height area.
 */

#ifndef CONTROLLERSEG2_H_
#define CONTROLLERSEG2_H_

#include "HALCallInterface.h"
#include "SegHeight.h"
#include "ControllerSeg3.h"

class ControllerSeg2: public HALCallInterface {
public:
	/**
	 * @return The controller's instance
	 */
	static ControllerSeg2* getInstance();

	void inHeightMeasurement();
	void outHeightMeasurement();
	void inToleranceRange();
	void notInToleranceRange();

	// Error's handling
	int sendMsg2Dispatcher(int message);
	void init();
	void passWP2Ctr();
	void reset();


	virtual ~ControllerSeg2();

private:
	ControllerSeg2();

	static ControllerSeg2* controllerSeg2_instance_;
	static Mutex controllerSeg2_mutex_; //!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEG2_H_ */
