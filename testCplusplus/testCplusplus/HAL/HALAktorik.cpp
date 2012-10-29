/*
 * HALAktorik.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: simohamed

*/
#include "HAL/HALAktorik.h"


using namespace std;

HALAktorik* HALAktorik::hal_Aktorik_instance_ = NULL;
Mutex* HALAktorik::hal_Aktorik_mutex_ = new Mutex();

HALAktorik::HALAktorik()
{

	// TODO  Implement Singelton Pattern HERE
	 // test Access' right
	 if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
	 perror("ThreadCtl access failed\n");
	 return;
	 }
	 // Initialize IO Card in case of success
	 led_ = new LED();
	 motor_ = new Motor();
	 light_ = new Light();
	 switch_ = new Switch();

	 out8(DIGITAL_CARD_CONTROL, 0x82);

}

HALAktorik::~HALAktorik()
{
	// TODO implements destructor HERE
	delete hal_Aktorik_mutex_;
}



HALAktorik* HALAktorik::getInstance()
{
	// TODO implements Singelton pattern HERE !
	if(!hal_Aktorik_instance_){
		hal_Aktorik_mutex_->lock();
		if(!hal_Aktorik_instance_){
			hal_Aktorik_instance_ = new HALAktorik;
		}
		hal_Aktorik_mutex_->unlock();
	}

	return hal_Aktorik_instance_;
}



void HALAktorik::Start_LED_on()
{
	led_->Start_LED_on();
}



void HALAktorik::motor_off()
{
	motor_->motor_off();
}



bool HALAktorik::is_Switch_Open()
{
	switch_->is_Switch_Open();
	return false;
}



void HALAktorik::red_Light_off()
{
	light_->red_Light_off();
}



void HALAktorik::Q2_LED_off()
{
	led_->Q2_LED_off();
}




void HALAktorik::Start_LED_off()
{
}



void HALAktorik::run_right()
{
	motor_->run_right();
}



void HALAktorik::run_left()
{
	motor_->run_left();
}



void HALAktorik::yellow_Light_on()
{
	light_->yellow_Light_on();
}



void HALAktorik::open_Switch()
{
	switch_->open_Switch();
}



void HALAktorik::Q2_LED_on()
{
	led_->Q2_LED_on();
}



void HALAktorik::close_Switch()
{
	switch_->close_Switch();
}



void HALAktorik::Reset_LED_on()
{
	led_->Reset_LED_on();
}



void HALAktorik::motor_on()
{
	motor_->motor_on();
}



void HALAktorik::green_Light_off()
{
	light_->green_Light_off();
}



void HALAktorik::green_Light_on()
{
	light_->green_Light_on();
}



void HALAktorik::stop_Motor()
{
	motor_->stop_Motor();
}



void HALAktorik::yellow_Light_off()
{
	light_->yellow_Light_off();
}



void HALAktorik::red_Light_on()
{
	light_->red_Light_on();
}



void HALAktorik::run_slow()
{
	motor_->run_slow();
}



void HALAktorik::Q1_LED_off()
{
	led_->Q1_LED_off();
}



void HALAktorik::Reset_LED_off()
{
	led_->Reset_LED_off();
}



void HALAktorik::Q1_LED_on()
{
	led_->Q1_LED_on();
}

