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
	init();

}
void Controller::init(){
	demultiplexer_ = Demultiplexer::getInstance();


		con_id_ = ConnectAttach(0, 0, demultiplexer_->getChannelId(), _NTO_SIDE_CHANNEL, 0);
		if (con_id_ == -1) {
			perror("Controller : ConnectAttach failed : ");
			exit(EXIT_FAILURE);
		}
#ifdef DEBUG_
		cout << "Controller attached to channelId: " << con_id_ << endl;
#endif
}

void Controller::inEngineStart()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<< " In Engine Start" << endl;
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	hal_aktorik_->red_Light_off();
	hal_aktorik_->Start_LED_on();

#endif
}

void Controller::outEngineStart()
{
}

void Controller::inHeightMeasurement()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<< " : In Height Measurement" << endl;
#endif
}

void Controller::outHeightMeasurement()
{
	cout << "Controller "<< this->getControllerId() <<": Out Height Measurement" << endl;
}

void Controller::inToleranceRange()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<": WP in Height's sensor " << endl;
#endif
}

void Controller::notInToleranceRange()
{
}

void Controller::isMetal()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<": WP has Metal : YES " << endl;
#endif
}

void Controller::notMetal()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<": WP has Metal : NO " << endl;
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
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<" : in Line end " << endl;
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	hal_aktorik_->red_Light_off();
	hal_aktorik_->close_Switch();
#endif
}

void Controller::outEngineEnd()
{
}

void Controller::startPressed()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<": Start button pressed " << endl;
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	hal_aktorik_->red_Light_off();
	hal_aktorik_->Start_LED_on();

#endif
}

void Controller::startReleased()
{
}

void Controller::stopPressed()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<" : Stop button pressed " << endl;
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	hal_aktorik_->Start_LED_off();
	hal_aktorik_->close_Switch();
	sendMsg2Dispatcher(WP_IS_MISSING);
#endif
}

void Controller::stopReleased()
{
}

void Controller::resetPressed()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<": Stop button pressed " << endl;
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	hal_aktorik_->Start_LED_off();
	hal_aktorik_->close_Switch();
	sendMsg2Dispatcher(WP_IS_MISSING);
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

void Controller::isMissing()
{
	cout << "Controller "<< this->getControllerId()<<": WP is missing " << endl;
	hal_aktorik_->red_Light_on();
}

/**
 * Send a message to Dispatcher
 */
int Controller::sendMsg2Dispatcher(int message){

	if (-1 == MsgSendPulse(con_id_,SIGEV_PULSE_PRIO_INHERIT, CONTROLLER_CODE, message )) {
		perror("Controller : MsgSendPulse");
		exit(EXIT_FAILURE);
	} else {
#ifdef DEBUG_
		cout << "Controller: message sent to dispatcher: " << message << " code " << CONTROLLER_CODE << endl;
#endif
	}
	return 0;
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
