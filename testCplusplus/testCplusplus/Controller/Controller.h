/*
 * @file	Controller.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	Nov 26, 2012
 *
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream.h>
#include "HALCallInterface.h"

class Controller: public HALCallInterface {
public:
	Controller();

	void inEngineStart();
	void outEngineStart();
	void inHeightMeasurement();
	void outHeightMeasurement();
	void inToleranceRange();
	void notInToleranceRange();
	void isMetal();
	void notMetal();
	void inSwitch();
	void outSwitch();
	void inSlide();
	void outSlide();
	void inEngineEnd();
	void outEngineEnd();
	void startPressed();
	void startReleased();
	void stopPressed();
	void stopReleased();
	void resetPressed();
	void resetReleased();
	void EStopPressed();
	void EStopReleased();

	virtual ~Controller();
};

#endif /* CONTROLLER_H_ */
