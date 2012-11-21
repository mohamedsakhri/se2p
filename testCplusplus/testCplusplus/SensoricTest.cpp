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
	int portB_old_value; // used to compare new value from pulse with the old value to know what has been changed
	int portC_old_value; // used to compare new value from pulse with the old value to know what has been changed
	int test_coid; // used for connectAttach with halSensoruíc channel

	bool height_ok = false;
	bool is_metal = false;
	bool switch_open = false;

	// get the default value of port B and C. This will be executed just the first time
	portB_old_value = in8(DIGITAL_CARD_CROUP0_PORTB);
	portC_old_value = in8(DIGITAL_CARD_CROUP0_PORTC);

	test_coid = ConnectAttach(0, 0, hal_sensoric_->getChannelId(),
			_NTO_SIDE_CHANNEL, 0);
	if (test_coid == -1) {
		perror("Test_Sensoric: ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}

	while (!isStopped()) {

#ifdef DEBUG_
		cout << " waiting for MsgReceivePulse " << endl;
#endif
		// Receive pulse messages from HAL Sensoric (Interrupt handler) channel and react
		if (-1 == MsgReceivePulse(hal_sensoric_->getChannelId(), &pulse,
				sizeof(pulse), NULL)) {
			cout << " MsgReceivePulse = -1 " << endl;
			if (isStopped()) {
				break; // channel destroyed, Thread ending
			}
			perror("SensoricTest: MsgReceivePulse");
			exit(EXIT_FAILURE);
		}

		//		cout << "TEST port : " << hex << (int) pulse.code << " Value : "
		//				<< pulse.value.sival_int << endl;

		int changed_bit = -1;
		int new_value = -1;
		new_value = pulse.value.sival_int;

		switch (pulse.code) {
		case IIR_PORTB:
			// which bit has been changed ?
			changed_bit = portB_old_value ^ new_value;

			// update old value with the new one
			portB_old_value = new_value;

			switch (changed_bit) {
			case BIT_0:
				if (new_value & BIT_0) {
					cout << "Workspace in LB 1 " << endl;
					HALAktorik::getInstance()->motor_on();
					HALAktorik::getInstance()->green_Light_on();
				} else {
					cout << " No workspace in LB 1" << endl;
				}

				break;
			case BIT_1:
				if (new_value & BIT_1) {
					cout << "No workspace in height measurement" << endl;
				} else {
					cout << "Workspace in height measurement" << endl;
				}
				break;
			case BIT_2:
				if (new_value & BIT_2) {
					cout << "Workspace's height : Ok - in tolerance range"
							<< endl;
					height_ok = true;
				} else {
					cout
							<< "Workspace's height : Not OK - too small or too high"
							<< endl;
					height_ok = false;
					//get exact height
					//int height = hal_sensoric_->calculateHeight();
				}
				break;
			case BIT_3:
				if (new_value & BIT_3) {
					cout << "No workspace in Switch" << endl;
					if (switch_open) {
						HALAktorik::getInstance()->close_Switch();
						switch_open = false;
					}

				} else {
					cout << "Workspace in Switch" << endl;
				}
				break;
			case BIT_4:
				if (new_value & BIT_4) {
					cout << "workspace metal : YES" << endl;
					is_metal = true;
				} else {
					cout << "workspace metal : NO" << endl;
					is_metal = false;
				}
				break;
			case BIT_5:
				if (new_value & BIT_5) {
					if (!height_ok) {
						cout << "Switch is open" << endl;
						switch_open = true;
					}
				} else {
					cout << "Switch is closed" << endl;
				}
				break;
			case BIT_6:
				if (new_value & BIT_6) {
					cout << "Slide not full" << endl;
				} else {
					cout << "Slide full" << endl;
				}
				break;
			case BIT_7:
				if (new_value & BIT_7) {
					cout << "No workspace in the end of the band " << endl;
				} else {
					cout << "Workspace in in the end of the band" << endl;
					HALAktorik::getInstance()->motor_off();
					HALAktorik::getInstance()->green_Light_off();
				}
				break;
			default:
				break;
			}
			break;
		case IIR_PORTC:
			// which bit has been changed ?
			changed_bit = portC_old_value ^ new_value;

			// update old value with the new one
			portC_old_value = new_value;
			switch (changed_bit) {
			case BIT_4:
				if (new_value & BIT_4) {
					cout << "Start button : ON" << endl;
				} else {
					cout << "Start button : OFF" << endl;
				}
				break;
			case BIT_5:
				if (new_value & BIT_5) {
					cout << "Reset button : ON" << endl;
				} else {
					cout << "Reset button : off" << endl;
				}
				break;

			case BIT_6:
				if (new_value & BIT_6) {
					cout << "Stop button : ON" << endl;
				} else {
					cout << "Stop button : OFF" << endl;
				}
				break;
			case BIT_7:
				if (new_value & BIT_7) {
					cout << "E-Stop button : ON" << endl;
				} else {
					cout << "E-Stop button : OFF" << endl;
				}
				break;
			default :
			break;
			}
		default:
			break;

			// just for test

		}
	}
}

void SensoricTest::shutdown() {
}

