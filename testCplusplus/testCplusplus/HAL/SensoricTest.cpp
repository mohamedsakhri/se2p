/*
 * @file	SensoricTest.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date	Nov 19, 2012
 *
 *
 * This class implements some regression tests
 */

//#define DEBUG_
#include "SensoricTest.h"

#define METAL_TEST
#define HEIGHT_TEST
/**
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
 * and detach from channel
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
	int new_value = -1;
	int old_port_value; // used to compare new value from pulse with the old value to know what has been changed
	int test_coid; 		// used for connectAttach with halSensoruíc channel
	int changed_bits = -1;
	int current_bit = -1;

	bool is_height_ok = false;	// true if workpiece's height in tolerance range
	bool is_metal = false;
	bool is_switch_open = false;

	// get the default value of port B and C.
	old_port_value = (in8(DIGITAL_CARD_CROUP0_PORTB)<<8)|(in8(DIGITAL_CARD_CROUP0_PORTC));

	// connect with HALSencsoric's channel to get pulses
	test_coid = ConnectAttach(0, 0, hal_sensoric_->getChannelId(), _NTO_SIDE_CHANNEL, 0);
	if (test_coid == -1) {
		perror("Test_Sensoric: ConnectAttach failed : ");
		exit(EXIT_FAILURE);
	}

	while (!isStopped()) {

		#ifdef DEBUG_
			cout << " waiting for MsgReceivePulse " << endl;
		#endif

		// Receive pulse messages from HAL Sensoric's (Interrupt handler) channel and react
		if (-1 == MsgReceivePulse(hal_sensoric_->getChannelId(), &pulse,
				sizeof(pulse), NULL)) {
			if (isStopped()) {
				break; // channel destroyed, Thread ending
			}
			perror("SensoricTest: MsgReceivePulse");
			exit(EXIT_FAILURE);
		}

		new_value = pulse.value.sival_int;
		changed_bits = new_value ^ old_port_value;	// which bits have been changed
		old_port_value = pulse.value.sival_int;		// update old value with the new one

		// shift 12 bits right. First 4 bits from port C are useless here
		changed_bits >>= 4;
		new_value >>= 4;

		#ifdef DEBUG_
			cout << "TEST port : " << hex << (int) pulse.code << " Value : "<< (int) new_value << endl;
		#endif

		// check all the 12 bits and react
		for (int i=0;i<=12;i++){
			current_bit = (1<<i);
			if (changed_bits & current_bit){ // if the bit has changed
//				cout << " current_bit: "<< hex << (int)current_bit << endl;
				switch (current_bit) {

				case START_BUTTON:		// Start Button
					if (new_value & START_BUTTON) {
						cout << "Start button pressed " << endl;
						hal_aktorik_->motor_on();
						hal_aktorik_->green_Light_on();
						hal_aktorik_->Start_LED_on();
					}
					break;
				case STOP_BUTTON:		//Stop Button
					if (!(new_value & STOP_BUTTON)) {
						cout << "Stop button pressed " << endl;
						hal_aktorik_->motor_off();
						hal_aktorik_->green_Light_off();
						hal_aktorik_->Start_LED_off();
						hal_aktorik_->close_Switch();
					}
					break;
				case RESET_BUTTON: 		//Reset Button
					if (new_value & RESET_BUTTON) {
						cout << "Reset button pressed " << endl;
					}
					break;
				case E_STOP_BUTTON:		//E-Stop
					if (new_value & E_STOP_BUTTON) {
						cout << "E-Stop button : released" << endl;
					} else {
						cout << "E-Stop button : pressed" << endl;
						hal_aktorik_->close_Switch();
						hal_aktorik_->motor_off();
						hal_aktorik_->green_Light_off();
						hal_aktorik_->Start_LED_off();
					}
					break;
				case ENGINE_START:		//Light Barrier 1
					if ( !(new_value & ENGINE_START)) {
						cout << "WP in engine's start " << endl;
						hal_aktorik_->motor_on();
						hal_aktorik_->green_Light_on();
						is_metal = false;
//						is_switch_open = false;
						is_height_ok = false;
					}
					break;
				case HEIGHT_SENSOR:		//WP in HeightSensor  LB2
					if (!(new_value & HEIGHT_SENSOR)) {
//						cout << "Workpiece in height measurement" << endl;
						// start height measurement
//						height = hal_sensoric_->calculateHeight();
//						cout << " Height : " << height << endl;

						// getting around the height's measurement by checking height's tolerance
						// range when workpiece in height's sensor
						if (new_value & HEIGHT_STATUS){
							cout << "WP hat Loch nach UNTEN " << endl;
						}
						else{
							if (is_height_ok){
								cout << "WP hat Loch nach OBEN  " << endl;

							}
							else {
								cout << "WP ist FLACH  " << endl;
								is_height_ok = false;
							}
						}
					}
					break;
				case HEIGHT_STATUS:		//HeightSensor tolerance range
					if (new_value & HEIGHT_STATUS) {
//						cout << "Workpiece's height in tolerance range"	<< endl;
						is_height_ok = true;
					}
					break;
				case WP_IS_IN_SWITCH:	// P in switch  LB3
					if (new_value & WP_IS_IN_SWITCH) {
						if (is_switch_open) {
							hal_aktorik_->close_Switch();
							is_switch_open = false;
						}
					} else {
#ifdef HEIGHT_TEST
						if (is_height_ok){
							hal_aktorik_->open_Switch();
						}
#endif
#ifdef METAL_TEST
						if ( is_metal) {
							hal_aktorik_->open_Switch();
						}
#endif
					}
					break;
				case METAL_STATUS:		// Metal Sensor
					if (new_value & METAL_STATUS) {
						cout << "WP has metal : YES" << endl;
						is_metal = true;
					} else {
						cout << "WP has metal : NO" << endl;
						is_metal = false;
					}
					break;
				case SWITCH_STATUS:		//Switch
					if (new_value & SWITCH_STATUS) {
						cout << "Switch is open" << endl;
						is_switch_open = true;
					} else {
						cout << "Switch is closed" << endl;
					//	switch_open = false;
					}
					break;
				case SLIDE_STATUS:		//Slide
					if (new_value & SLIDE_STATUS) {
						cout << "WP out Slide" << endl;
					} else {
						cout << "WP in Slide" << endl;

					}
					break;
				case ENGINE_END:		// LB end
					if (!(new_value & ENGINE_END)) {
						cout << "WP in engine's end " << endl;
						hal_aktorik_->motor_off();
						hal_aktorik_->green_Light_off();
						hal_aktorik_->Start_LED_off();
					}
					break;
				default :
				break;
				} // switch (current_bit)
			} //if (changed_bits & current_bit)
		} // for
	} // while
}

void SensoricTest::shutdown() {

}

