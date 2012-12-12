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
	static ControllerSeg3* getInstance();

	void inSwitch();
	void outSwitch();

	// Error's handling
	int sendMsg2Dispatcher(int message);
	void init();
	void passWP2Ctr();
	void passWP2Ctr(int ctr_id);
	virtual ~ControllerSeg3();

private:
	ControllerSeg3();

	static ControllerSeg3* controllerSeg3_instance_;
	static Mutex controllerSeg3_mutex_; //!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEG3_H_ */
