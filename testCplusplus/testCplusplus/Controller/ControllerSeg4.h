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
//TODO .h of slide
#include "SegSwitch.h"

class ControllerSeg4: public HALCallInterface {
public:
	static ControllerSeg4* getInstance();

	void inSlide();
	void outSlide();

	// Error's handling
	int sendMsg2Dispatcher(int message);
	void init();
	void passWP2Ctr();

	virtual ~ControllerSeg4();

private:
	ControllerSeg4();

	static ControllerSeg4* controllerSeg4_instance_;
	static Mutex controllerSeg4_mutex_; //!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEG4_H_ */
