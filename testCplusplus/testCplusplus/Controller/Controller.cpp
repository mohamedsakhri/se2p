/*
 * @file 	Controller.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Nov 26, 2012
 *
 */

#include "Controller.h"

Controller::Controller() {

}

void Controller::inEngineStart()
{
	cout << "Controller : In Engine Start" << endl;
}

void Controller::outEngineStart()
{
	cout << "Out Engine Start" << endl;
}

void Controller::inHeightMeasurement()
{
	cout << "Controller In Height Measurement" << endl;
}

void Controller::outHeightMeasurement()
{
	cout << "Out Height Measurement" << endl;
}

void Controller::inToleranceRange()
{
}

void Controller::notInToleranceRange()
{
}

void Controller::isMetal()
{
}

void Controller::notMetal()
{
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
}

void Controller::startReleased()
{
}

void Controller::stopPressed()
{
}

void Controller::stopReleased()
{
}

void Controller::resetPressed()
{
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

/**
 *
 */
void Controller::addEvent(int event_index)
{
	events_list_.push_back(event_index);
}

/**
 *
 */
vector<int> Controller::getEvents()
{
	return events_list_;
}


Controller::~Controller() {
	// TODO Auto-generated destructor stub
}
