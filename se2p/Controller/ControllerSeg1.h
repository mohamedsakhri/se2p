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
	/**
	 * @return The controller's instance
	 */
	static ControllerSeg1* getInstance();
	/**
	 * What to do when WP in in Line start
	 */
	void inLineStart();

	/**
	 * What to do when WP in in Line start
	 */
	void outLineStart();

	/**
	 * @param message Message to be sent.
	 */
	int sendMsg2Dispatcher(int message);

	/**
	 * Initialize connection with demultiplexers' channel
	 */
	void init();

	/**
	 * Pass a WP to next segment's controller
	 */
	void passWP2Ctr();

	/**
	 * Reset controller
	 */
	void reset();

	/**
	 * Deconstructor
	 */
	virtual ~ControllerSeg1();

private:
	ControllerSeg1();

	static ControllerSeg1 *controllerSeg1_instance_ ;	//!< Controller's instance
	static Mutex controllerSeg1_mutex_; 				//!< Mutex for thread-safe implementation
};

#endif /* CONTROLLERSEG1_H_ */
