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
//	hal_aktorik_ = HALAktorik::getInstance();
	inLine_state_ = new StateLineStart(this);
	height_state_ = new WaitingHeightM1(this);
	switch_state_ = new WaitingSwitch(this);

	init();
}

//TODO comment and implement
/**
 * Copy-Constructor
 *
 */
Controller::Controller(const Controller& ctr) {

}

/**
 * Do some initialization work
 */
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
//	state = new StateLineStart(this);

	inLine_state_->inLineStart();
}

void Controller::outEngineStart()
{
	inLine_state_->outLineStart();
	this->passWP2Ctr(height_state_->controller);

}

void Controller::inHeightMeasurement()
{
	height_state_->inHeightMeasurement();
}

void Controller::outHeightMeasurement()
{
	height_state_->outHeightMeasurement();
	this->passWP2Ctr(height_state_->controller);
}

void Controller::inToleranceRange()
{
	height_state_->inToleranceRange();
}

void Controller::notInToleranceRange()
{
	height_state_->notInToleranceRange();
}

void Controller::isMetal()
{
}

void Controller::notMetal()
{
}

void Controller::inSwitch()
{
	switch_state_->inSwitch();
}

void Controller::outSwitch()
{
	switch_state_->outSwitch();
}

void Controller::switchOpen()
{
	switch_state_->switchOpen();
}

void Controller::switchClosed()
{
	switch_state_->switchClosed();
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
	HALAktorik::getInstance()->motor_off();
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

void Controller::isMissing()
{
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

void Controller::addWP2List(WorkPiece wp)
{
	wp_list_.push_back(wp);
}

WorkPiece Controller::getLastWP()
{
	return wp_list_.at(wp_list_.size());
}


void Controller::removeLastWP()
{
	wp_list_.pop_back();
}

void Controller::passWP2Ctr(HALCallInterface* ctr)
{
	ctr->addWP2List(getLastWP());
}


Controller::~Controller() {
	// TODO Auto-generated destructor stub
}
