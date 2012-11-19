/*
 * SensoricTest.cpp
 *
 *  Created on: Nov 19, 2012
 *      Author: simohamed
 */

#define DEBUG_
#include "SensoricTest.h"

/**
 * Singleton pattern implemetation, thread safe implemented
 * get HALSensoric and HALAktorik's Instances or created new ones
 */
SensoricTest::SensoricTest() {
#ifdef DEBUG_
	cout << " SensoricTest cunstructor started ... " << endl;
#endif
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
			perror("ThreadCtl access failed\n");
			exit(EXIT_FAILURE);
	}

	hal_aktorik_ = HALAktorik::getInstance();
	hal_sensoric_ = HALSensoric::getInstance();
}

/**
 * Free memory allocated by HALSensoric and HALAktorik's Instances
 */

SensoricTest::~SensoricTest() {
	delete hal_aktorik_;
	delete hal_sensoric_;
}

/**
 * All tests will be implemented here ! Using macros could filter which one will be started
 */
void SensoricTest::execute(void *arg) {
#ifdef DEBUG_
	cout << " SensoricTest started ... " << endl;
#endif
		struct _pulse pulse;
		int old_value ;  		// used to compare new value from pulse with the old value
								// to know what has been changed

		while (!isStopped()) {
			// Receive pulse messages from HAL Sensoric channel and react
		if (-1 == MsgReceivePulse(hal_sensoric_->getChannelId(), &pulse,
				sizeof(pulse), NULL)) {
			if (isStopped()) {
				break; // channel destroyed, Thread ending
			}
			perror("SensoricTest: MsgReceivePulse");
			exit(EXIT_FAILURE);
		}

//		cout << " port : " << hex << (int) pulse.code << " Value : "
//				<< pulse.value.sival_int << endl;
		/*
		 *  JUST FOR TEST
		 */
		switch (pulse.value.sival_int) {
		/**
		 *  TO DO : NO MAGIC NUMBER AND CONTINUE ALL POSSIBLE TESTS
		 */

		case 0xCA:
			HALAktorik::getInstance()->motor_on();
			cout << " Default - port : " << hex << (int) pulse.code << endl;
			break;
		case 0x4B:
			HALAktorik::getInstance()->motor_off();
			cout << " Default - port : " << hex << (int) pulse.code << endl;
			break;
		case 0xC3:
			HALAktorik::getInstance()->open_Switch();
			cout << " Default - port : " << hex << (int) pulse.code << endl;
			break;
		default:
			break;
			//cout << " Default - port : " << hex << (int) pulse.code <<
			//" Value : " << pulse.value.sival_int << endl;
		}
		// just for test
		old_value = pulse.value.sival_int;
	}
}

void SensoricTest::shutdown() {

}

