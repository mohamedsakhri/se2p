/**
 * @file 	HALAktorik.cpp
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date	Oct 18, 2012
 *
 */

#include "HALAktorik.h"
#include <iostream>

using namespace std;

HALAktorik* HALAktorik::hal_Aktorik_instance_ = NULL;
Mutex HALAktorik::hal_Aktorik_mutex_ = Mutex();

/**
 * Initialization of portA and PortC
 *
 */
HALAktorik::HALAktorik() {
	portA_ = new PortA();
	portC_ = new PortC();
}

/**
 * Free memory allocated by HAL.
 *\see HALAktorik()
 */
HALAktorik::~HALAktorik() {
	delete portA_;
	delete portC_;
	delete hal_Aktorik_instance_;
}

/**
 * return an Instance of the HALAktorik and initialize the IO_CARD
 * At most one instance of HALAktorik will be created.
 * If no instance has been created yet, a new instance has to be created.
 * Otherwise the already created instance will be returned.
 *
 */
HALAktorik* HALAktorik::getInstance() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
			perror("ThreadCtl access failed\n");
			return NULL;
		}

	if (!hal_Aktorik_instance_) {
		hal_Aktorik_mutex_.lock();
		if (!hal_Aktorik_instance_) {
			hal_Aktorik_instance_ = new HALAktorik;
			out8(DIGITAL_CARD_CONTROL, 0x8A);
		}
		hal_Aktorik_mutex_.unlock();
	}


	return hal_Aktorik_instance_;
}

/************************************************************************************
 *									MOTOR											*
 *																					*
 ************************************************************************************/

void HALAktorik::motor_on() {
	portA_->motor_on();
}

void HALAktorik::motor_off() {
	portA_->motor_off();
}

/**
 *  Motor could be stopped by changing BIT_3, not changing BIT_1, BIT_2 or BIT_3
 *  could be used to hold the band for a defined time too.
 */
void HALAktorik::stop_Motor() {
	portA_->stop_Motor();
}

void HALAktorik::start_Motor(){
	portA_->start_Motor();
}

void HALAktorik::run_right() {
	portA_->run_right();
}

void HALAktorik::run_left() {
	portA_->run_left();
}

void HALAktorik::run_slow() {
	portA_->run_slow();
}


/************************************************************************************
 *									SWITCH											*
 *																					*
 ************************************************************************************/

void HALAktorik::open_Switch() {
	portA_->open_Switch();
}

void HALAktorik::close_Switch() {
	portA_->close_Switch();
}

bool HALAktorik::is_Switch_Open() {
	return (portA_->is_Switch_Open());
}


/************************************************************************************
 *									LIGHTS											*
 *																					*
 ************************************************************************************/

void HALAktorik::green_Light_on() {
	portA_->green_Light_on();
}

void HALAktorik::green_Light_off() {
	portA_->green_Light_off();
}

void HALAktorik::red_Light_on() {
	portA_->red_Light_on();
}

void HALAktorik::red_Light_off() {
	portA_->red_Light_off();
}

void HALAktorik::yellow_Light_on() {
	portA_->yellow_Light_on();
}

void HALAktorik::yellow_Light_off() {
	portA_->yellow_Light_off();
}


/************************************************************************************
 *									LEDs											*
 *																					*
 ************************************************************************************/

void HALAktorik::Q1_LED_on() {
	portC_->Q1_LED_on();
}

void HALAktorik::Q1_LED_off() {
	portC_->Q1_LED_off();
}

void HALAktorik::Q2_LED_on() {
	portC_->Q2_LED_on();
}

void HALAktorik::Q2_LED_off() {
	portC_->Q2_LED_off();
}

void HALAktorik::Start_LED_on() {
	portC_->Start_LED_on();
}

void HALAktorik::Start_LED_off() {
	portC_->Start_LED_off();
}

void HALAktorik::Reset_LED_on() {
	portC_->Reset_LED_on();
}

void HALAktorik::Reset_LED_off() {
	portC_->Reset_LED_off();
}
