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

#ifndef CONTROLLERSEG5_H_
#define CONTROLLERSEG5_H_

#include "HALCallInterface.h"
#include "WaitingSwitch.h"

class ControllerSeg5: public HALCallInterface {
public:
	static ControllerSeg5* getInstance();

	void inLineEnd();
	void outLineEnd();

	// Error's handling
	int sendMsg2Dispatcher(int message);
	void init();
	void passWP2Ctr();

	virtual ~ControllerSeg5();

private:
	ControllerSeg5();

	static ControllerSeg5* controllerSeg5_instance_;
	static Mutex controllerSeg5_mutex_; //!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEG5_H_ */
