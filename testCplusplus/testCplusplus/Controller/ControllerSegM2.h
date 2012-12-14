/*
 * @file 	ControllerSegM2.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 14, 2012
 *
 * This class represents the controller of Machine 2.
 *
 */

#ifndef CONTROLLERSEGM2_H_
#define CONTROLLERSEGM2_H_

#include "HALCallInterface.h"
#include "SegMachine2.h"

class ControllerSegM2: public HALCallInterface {
public:
	static ControllerSegM2* getInstance();

	void inLineStart();				//!< WP in Line's start
	void inHeightMeasurement();		//!< WP is in height measurement area
	void outHeightMeasurement();		//!< WP has left height measurement area
	void inToleranceRange();			//!< WP's height is in tolerance range
	void isMetal();						//!< WP has metal
	void outSwitch();					//!< WP has left Switch area
	void inSwitch();
	void outSlide();					//!< WP out Slide's light barrier
	void outLineEnd();


	// Error's handling
	int sendMsg2Dispatcher(int message);
	void init();
	void passWP2Ctr();

	virtual ~ControllerSegM2();

private:
	ControllerSegM2();

	static ControllerSegM2* controllerSegM2_instance_;
	static Mutex controllerSegM2_mutex_; //!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEGM2_H_ */
