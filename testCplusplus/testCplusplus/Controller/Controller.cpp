/*
 * @file 	Controller.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Nov 26, 2012
 *
 */

#define DISPATCHER_TEST
#include "Controller.h"

int Controller::ctr_number_ = 0;

/**
 * Assigne an id to this controller
 */
Controller::Controller() {
	ctr_id_= ctr_number_++;
	hal_aktorik_ = HALAktorik::getInstance();
}

void Controller::inEngineStart()
{
#ifdef DISPATCHER_TEST
	cout << "Controller : In Engine Start" << endl;
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	hal_aktorik_->Start_LED_on();

#endif
}

void Controller::outEngineStart()
{
	cout << "Out Engine Start" << endl;
}

void Controller::inHeightMeasurement()
{
#ifdef DISPATCHER_TEST
	cout << "Controller : In Height Measurement" << endl;
#endif
}

void Controller::outHeightMeasurement()
{
	cout << "Out Height Measurement" << endl;
}

void Controller::inToleranceRange()
{
#ifdef DISPATCHER_TEST
	cout << "Controller : WP in Height's sensor " << endl;
#endif
}

void Controller::notInToleranceRange()
{
}

void Controller::isMetal()
{
#ifdef DISPATCHER_TEST
	cout << "Controller : WP has Metal : YES " << endl;
#endif
}

void Controller::notMetal()
{
#ifdef DISPATCHER_TEST
	cout << "Controller : WP has Metal : NO " << endl;
#endif
}

void Controller::inSwitch()
{
}

void Controller::outSwitch()
{
}

void Controller::switchOpen()
{

}

void Controller::switchClosed()
{

}

void Controller::inSlide()
{
}

void Controller::outSlide()
{
}

void Controller::inEngineEnd()
{
}

void Controller::outEngineEnd()
{
}

void Controller::startPressed()
{
#ifdef DISPATCHER_TEST
	cout << "Controller : Start button pressed " << endl;
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	hal_aktorik_->Start_LED_on();
#endif
}

void Controller::startReleased()
{
}

void Controller::stopPressed()
{
#ifdef DISPATCHER_TEST
	cout << "Controller : Stop button pressed " << endl;
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	hal_aktorik_->Start_LED_off();
	hal_aktorik_->close_Switch();
#endif
}

void Controller::stopReleased()
{
}

void Controller::resetPressed()
{
#ifdef DISPATCHER_TEST
	cout << "Controller : Stop button pressed " << endl;
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	hal_aktorik_->Start_LED_off();
	hal_aktorik_->close_Switch();
#endif

}

void Controller::resetReleased()
{
}

void Controller::EStopPressed()
{
}

void Controller::EStopReleased()
{
}

int Controller::getControllerId()
{
	return ctr_id_;
}

/**
 * Add an event to controller
 */
void Controller::addEvent(int event_index)
{
	events_list_.push_back(event_index);
}

/**
 * Return al list of events the controller is registered to
 */
vector<int> Controller::getEvents()
{
	return events_list_;
}


Controller::~Controller() {
	// TODO Auto-generated destructor stub
}
