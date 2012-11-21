/*
 * SensoricTest.cpp
 *
 *  Created on: Nov 19, 2012
 *      Author: simohamed
 */

//#define DEBUG_
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
	uint16_t new_value = -1;
	uint16_t old_port_value; // used to compare new value from pulse with the old value to know what has been changed
	int test_coid; 		// used for connectAttach with halSensoruíc channel
	uint16_t changed_bits = -1;
	int current_bit =-1;


	bool height_ok = false;
	bool is_metal = false;
	bool switch_open = false;

	// get the default value of port B and C.
	old_port_value = (in8(DIGITAL_CARD_CROUP0_PORTB)<<8)|(in8(DIGITAL_CARD_CROUP0_PORTC));


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
			if (isStopped()) {
				break; // channel destroyed, Thread ending
			}
			perror("SensoricTest: MsgReceivePulse");
			exit(EXIT_FAILURE);
		}



#ifdef DEBUG_
		cout << "TEST port : " << hex << (int) pulse.code << " Value : "
		<< (int) new_value  << endl;
#endif
		new_value = pulse.value.sival_int;
		changed_bits = new_value ^ old_port_value;
		old_port_value = pulse.value.sival_int;

		changed_bits >>= 4;
		new_value >>= 4;
		for (int i=0;i<=12;i++){
			current_bit = (1<<i);
			if (changed_bits & current_bit){
				cout << " current_bit: "<< hex << (int)current_bit << endl;
				switch (current_bit) {

				case BIT_0:		// Start Button
					if (new_value & BIT_0) {
						cout << "Start button " << endl;
						HALAktorik::getInstance()->motor_on();
					}
					break;
				case BIT_1:		//Stop Button
					if (!(new_value & BIT_1)) {
						cout << "Stop button " << endl;
						HALAktorik::getInstance()->close_Switch();
						HALAktorik::getInstance()->motor_off();
						HALAktorik::getInstance()->green_Light_off();
					}
					break;
				case BIT_2: 	//Reset Button
					if (new_value & BIT_2) {
						cout << "Reset button " << endl;
					}
					break;
				case BIT_3:		//E-Stop
					if (new_value & BIT_3) {
						cout << "E-Stop button : not pressed" << endl;
					} else {
						cout << "E-Stop button : pressed" << endl;
					}
					break;
				case BIT_4:		//Light Barrier 1
					if ( !(new_value & BIT_4)) {
						cout << "Workpiece in LB 1 " << endl;
						HALAktorik::getInstance()->motor_on();
						HALAktorik::getInstance()->green_Light_on();
					}
					break;
//TODO
				case BIT_5:		//WP in HeightSensor  LB2
					if (!(new_value & BIT_5)) {
						cout << "Workpiece in height measurement" << endl;

						if (new_value & BIT_2){
							cout << " P hat loch nach UNTEN " << endl;
						}
						else{
							if (height_ok){
								cout << " P hat loch nach OBEN  " << endl;
							}
							else
								cout << " P ist FLACH  " << endl;
						}
					}
					else
						cout << "No Workpiece in height measurement" << endl;

					break;
				case BIT_6:		//HeightSensor tolerance range
					if (new_value & BIT_6) {
						cout << "Workpiece's height in tolerance range"	<< endl;
						height_ok = true;
					} else {
						cout << "Workpiece's height NOT in tolerance range"	<< endl;
					}
					break;
				case BIT_7:		// P in switch  LB3
					if (new_value & BIT_7) {
						cout << "No Workpiece in Switch BIT = 1" << endl;
						cout << "switch open: " << switch_open << endl;
						if (switch_open) {
							HALAktorik::getInstance()->close_Switch();
							switch_open = false;
						}
					} else {
						cout << "Workpiece in Switch BIT = 0" << endl;
						cout << "BIT = 0 switch open: " << switch_open << endl;
						if (is_metal){
						HALAktorik::getInstance()->open_Switch();
						}
					}
					break;
				case BIT_8:		// Metall Sensor
					if (new_value & BIT_8) {
						cout << "Workpiece metal : YES" << endl;
						is_metal = true;
					} else {
						cout << "Workpiece metal : NO" << endl;
						is_metal = false;
					}
					break;
				case BIT_9:		//Switch
					if (new_value & BIT_9) {
						cout << "Switch is open" << endl;
						switch_open = true;
					} else {
						cout << "Switch is closed" << endl;
					//	switch_open = false;
					}
					break;
				case BIT_10:	//Slide
					if (new_value & BIT_10) {
	//					cout << "Slide not full" << endl;
					} else {
	//					cout << "Slide full" << endl;

					}
					break;
				case BIT_11:	// LB end
					if (!(new_value & BIT_11)) {
						cout << "Workpiece in in the end of the band " << endl;
						HALAktorik::getInstance()->motor_off();
						HALAktorik::getInstance()->green_Light_off();
					}
					break;


				default :
				break;
				}

			}
		}
	}
}

void SensoricTest::shutdown() {
}

