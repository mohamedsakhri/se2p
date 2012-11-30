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
#include "ControllerTest.h"

int ControllerTest::ctr_number_ = 0;

/**
 * Assigne an id to this controller
 */
ControllerTest::ControllerTest() {
	ctr_id_= ctr_number_++;
	hal_aktorik_ = HALAktorik::getInstance();
	init();

}
void ControllerTest::init(){
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

void ControllerTest::inEngineStart()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<< " In Engine Start" << endl;
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	hal_aktorik_->red_Light_off();
	hal_aktorik_->Start_LED_on();

#endif
}

void ControllerTest::outEngineStart()
{
}

void ControllerTest::inHeightMeasurement()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<< " : In Height Measurement" << endl;
#endif
}

void ControllerTest::outHeightMeasurement()
{
	cout << "Controller "<< this->getControllerId() <<": Out Height Measurement" << endl;
}

void ControllerTest::inToleranceRange()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<": WP in Height's sensor " << endl;
#endif
}

void ControllerTest::notInToleranceRange()
{
}

void ControllerTest::isMetal()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<": WP has Metal : YES " << endl;
#endif
}

void ControllerTest::notMetal()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<": WP has Metal : NO " << endl;
#endif
}

void ControllerTest::inSwitch()
{
}

void ControllerTest::outSwitch()
{
}

void ControllerTest::switchOpen()
{

}

void ControllerTest::switchClosed()
{

}

void ControllerTest::inSlide()
{
}

void ControllerTest::outSlide()
{
}

void ControllerTest::inEngineEnd()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<" : in Line end " << endl;
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	hal_aktorik_->red_Light_off();
	hal_aktorik_->close_Switch();
#endif
}

void ControllerTest::outEngineEnd()
{
}

void ControllerTest::startPressed()
{
#ifdef DISPATCHER_TEST
	cout << "Controller "<< this->getControllerId()<<": Start button pressed " << endl;
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	hal_aktorik_->red_Light_off();
	hal_aktorik_->Start_LED_on();

#endif
}

void ControllerTest::startReleased()
{
}

void ControllerTest::stopPressed()
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

void ControllerTest::stopReleased()
{
}

void ControllerTest::resetPressed()
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

void ControllerTest::resetReleased()
{
}

void ControllerTest::EStopPressed()
{
}

void ControllerTest::EStopReleased()
{
}

void ControllerTest::isMissing()
{
	cout << "Controller "<< this->getControllerId()<<": WP is missing " << endl;
	hal_aktorik_->red_Light_on();
	hal_aktorik_->green_Light_off();
}

/**
 * Send a message to Dispatcher
 */
int ControllerTest::sendMsg2Dispatcher(int message){

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

int ControllerTest::getControllerId()
{
	return ctr_id_;
}

/**
 * Add an event to controller
 */
void ControllerTest::addEvent(int event_index)
{
	events_list_.push_back(event_index);
}

/**
 * Return al list of events the controller is registered to
 */
vector<int> ControllerTest::getEvents()
{
	return events_list_;
}


ControllerTest::~ControllerTest() {
	// TODO Auto-generated destructor stub
}
