/*
 * @file	SensoricTest.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date	Nov 19, 2012
 *
 *
 * This class implements some regression tests
 */

#ifndef SENSORIKTEST_H_
#define SENSORIKTEST_H_
#include "HALSensoric.h"
#include "HALAktorik.h"
#include "HAWThread.h"

using namespace thread;

class SensoricTest: public HAWThread {
public:
	SensoricTest();
	virtual ~SensoricTest();

	virtual void execute(void* arg);
	virtual void shutdown();

private:
	HALAktorik* hal_aktorik_;			//!< HAL Aktorik instance
	HALSensoric* hal_sensoric_;			//!< HAL Sensoric instance
};

#endif /* SENSORIKTEST_H_ */
