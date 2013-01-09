/*
 * @file 	Controller.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Nov 26, 2012
 *
 *	Class created to be used in dispatcherTest. The events hander work directly with HALAktorik because the test has to be
 *	implemented before States machine are implemented.
 *
 */

#define DEBUG_

#include "ControllerTest.h"

int ControllerTest::ctr_number_ = 0;

/*
 * Assign an id to this controller
 */
ControllerTest::ControllerTest() {
	ctr_id_= ctr_number_++;
	hal_aktorik_ = HALAktorik::getInstance();
	init();

}

/*
 * Attach to Demultiplexer channel to send error's messages
 */
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

/*
 * Create Workpiece and add it to FIFO and call appropriate HALAktorik methods
 */
void ControllerTest::inLineStart()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<< " In Engine Start" << endl;
#endif
	WorkPiece* wp;
	wp = new WorkPiece();
	wp_list_.push_back(wp);
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	hal_aktorik_->red_Light_off();
	hal_aktorik_->Start_LED_on();
}

/*
 * WP left Line Start
 */
void ControllerTest::outLineStart()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<< " Out Engine Start" << endl;
#endif

}

void ControllerTest::inHeightMeasurement()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<< " : In Height Measurement" << endl;
#endif
}

void ControllerTest::outHeightMeasurement()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId() <<": Out Height Measurement" << endl;
#endif
}

void ControllerTest::inToleranceRange()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": WP in Tolerance range " << endl;
#endif
	getFirstWP()->setIs_inTolleranceRange(true);

}

void ControllerTest::notInToleranceRange()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": WP not in Tolerance range " << endl;
#endif
}

void ControllerTest::isMetal()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": WP has Metal : YES " << endl;
#endif
	getFirstWP()->setIs_Metal(true);

}

void ControllerTest::notMetal()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": WP has Metal : NO " << endl;
#endif
}

void ControllerTest::inSwitch()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": WP in switch " << endl;
#endif

	if (getFirstWP()->getIs_inTolleranceRange()){
		hal_aktorik_->open_Switch();
	}
}

void ControllerTest::outSwitch()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": WP out switch " << endl;
#endif
	hal_aktorik_->close_Switch();
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
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": WP out Slide " << endl;
#endif
	removeFirsttWP();
}

void ControllerTest::inLineEnd()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<" :WP in Line end " << endl;
#endif
	removeFirsttWP();
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	hal_aktorik_->red_Light_off();
	hal_aktorik_->close_Switch();
}

void ControllerTest::outLineEnd()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<" :WP out Line end " << endl;
#endif
}

void ControllerTest::startPressed()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": Start button pressed " << endl;
#endif
	hal_aktorik_->motor_on();
	hal_aktorik_->green_Light_on();
	hal_aktorik_->red_Light_off();
	hal_aktorik_->Start_LED_on();
}

void ControllerTest::startReleased()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": Start button released " << endl;
#endif
}

void ControllerTest::stopPressed()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<" : Stop button pressed " << endl;
#endif
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	hal_aktorik_->Start_LED_off();
//	hal_aktorik_->close_Switch();
//	sendMsg2Dispatcher(WP_IS_MISSING);
}

void ControllerTest::stopReleased()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<" : Stop button released " << endl;
#endif
}

void ControllerTest::resetPressed()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": Stop button pressed " << endl;
//	sendMsg2Dispatcher(WP_IS_MISSING);
#endif

}

void ControllerTest::resetReleased()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": Stop button released " << endl;
#endif
}

void ControllerTest::EStopPressed()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<":E-Stop button pressed " << endl;
#endif
	hal_aktorik_->motor_off();
	hal_aktorik_->green_Light_off();
	hal_aktorik_->Start_LED_off();
	hal_aktorik_->close_Switch();
}

void ControllerTest::EStopReleased()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<":E-Stop button released " << endl;
#endif
}

void ControllerTest::isMissing()
{
#ifdef DEBUG_
	cout << "Controller "<< this->getControllerId()<<": WP is missing " << endl;
#endif
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

/*
 * @return Cotnroller id
 */
int ControllerTest::getControllerId()
{
	return ctr_id_;
}

/*
 * Not used here
 */
void ControllerTest::passWP2Ctr() {

}

/**
 * Nothing to do !
 */
ControllerTest::~ControllerTest() {

}
