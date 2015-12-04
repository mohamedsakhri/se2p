/*
 * @file	StateTest.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Nov 11, 2012
 *
 * This class is used to test states' implementation.
 */

#ifndef STARTER_H_
#define STARTER_H_

#include "ControllerSeg1.h"
#include "ControllerSeg2.h"
#include "ControllerSeg3.h"
#include "ControllerSeg4.h"
#include "ControllerSeg5.h"
#include "ControllerSegM2.h"
#include "MainController.h"
#include "HAWThread.h"
#include "Dispatcher.h"

class Starter: public thread::HAWThread {
public:
	/**
	 * Constructor
	 */
	Starter();

	/**
	 * Deconstrucor
	 */
	virtual ~Starter();

	/**
	 * Method to be executed when thread starts
	 */
	void execute(void* arg);

	/**
	 * To be executed when thread stops.
	 */
	void shutdown();
};

#endif /* STATETASTE_H_ */
