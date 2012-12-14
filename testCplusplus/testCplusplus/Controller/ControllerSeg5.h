/*
 * @file 	ControllerSeg5.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * This class represents the controller of the third segment which controls the line's end area
 */

#ifndef CONTROLLERSEG5_H_
#define CONTROLLERSEG5_H_

#include "HALCallInterface.h"
#include "SegLineEnd.h"

class ControllerSeg5: public HALCallInterface {
public:
	static ControllerSeg5* getInstance();

	void inLineEnd();
	void outLineEnd();

	void m2isBusy();
	void m2isReady();

	bool isMachin2Ready() ;

	// Error's handling
	int sendMsg2Dispatcher(int message);
	void init();
	void passWP2Ctr();

	virtual ~ControllerSeg5();

private:
	ControllerSeg5();
	bool machine2_ready_;

	static ControllerSeg5* controllerSeg5_instance_;
	static Mutex controllerSeg5_mutex_; //!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEG5_H_ */
