/*
 * @file StateTest.cpp
 *
 * @author Mahmoud Dariti
 * @author Mohamed Sakhri
 *
 * @date Nov 11, 2012
 *
 * This class is used to test states' implementation.
 */

#include "StateTest.h"
#include "Constants.h"

#define TEST_MACHINE_1
//#define TEST_MACHINE_2

StateTest::StateTest() {
	dispatcher_ = Dispatcher::getInstance();
	HALAktorik::getInstance()->motor_off();
	HALAktorik::getInstance()->close_Switch();

}

StateTest::~StateTest() {
	// TODO Auto-generated destructor stub
}

void StateTest::execute(void *arg) {
	cout << "StateTaste started" << endl;
#ifdef TEST_MACHINE_1
	// ControllerSeg1 *ctr1 = ControllerSeg1::getInstance();
	// ControllerSeg2 *ctr2 = ControllerSeg2::getInstance();
	// ControllerSeg3 *ctr3 = ControllerSeg3::getInstance();
	// ControllerSeg4 *ctr4 = ControllerSeg4::getInstance();
	// ControllerSeg5 *ctr5 = ControllerSeg5::getInstance();

	MainController *mainCtr = MainController::getInstance();

	//
	// // Controllers add some events to register to
	// ctr1->addEvent(WP_IN_ENGINE_START);
	// ctr1->addEvent(WP_OUT_ENGINE_START);
	mainCtr->addEvent(START_PRESSED);
	mainCtr->addEvent(START_RELEASED);
	mainCtr->addEvent(STOP_PRESSED);
	mainCtr->addEvent(E_STOP_PRESSED);
	mainCtr->addEvent(E_STOP_RELEASED);
	mainCtr->addEvent(RESET_PRESSED);
	mainCtr->addEvent(RESET_RELEASED);
	mainCtr->addEvent(WP_IS_MISSING);
	mainCtr->addEvent(WP_IS_STRANGER);
	mainCtr->addEvent(SLIDE_FULL);
	mainCtr->addEvent(SLIDE_EMPTY);
	mainCtr->addEvent(WP_NOT_TURNED);


	//
	// ctr2->addEvent(WP_IN_HEIGHT_M);
	// ctr2->addEvent(WP_OUT_HEIGHT_M);
	// ctr2->addEvent(WP_IN_TOLERANCE_R);
	// ctr2->addEvent(WP_NOT_IN_TOLERANCE_R);
	//
	//
	//
	// ctr3->addEvent(WP_IN_SWITCH);
	// ctr3->addEvent(WP_OUT_SWITCH);
	//
	//
	//
	// ctr4->addEvent(WP_IN_SLIDE);
	// ctr4->addEvent(WP_OUT_SLIDE);
	//
	//
	//
	// ctr5->addEvent(WP_IN_ENGINE_END);
	// ctr5->addEvent(WP_OUT_ENGINE_END);
	// ctr5->addEvent(WP_HAS_ARRIVED);
	// ctr5->addEvent(MACHINE2_IS_BUSY);
	// ctr5->addEvent(MACHINE2_IS_READY);
	//

	// ctr3->addEvent(STOP_PRESSED);


	// Register Controllers for some events
	// dispatcher_->registerHandler(ctr1);
	// dispatcher_->registerHandler(ctr2);
	// dispatcher_->registerHandler(ctr3);
	// dispatcher_->registerHandler(ctr4);
	// dispatcher_->registerHandler(ctr5);
	dispatcher_->registerHandler(mainCtr);

#endif

#ifdef TEST_MACHINE_2
	MainController *mainCtr = MainController::getInstance();
	// ControllerSegM2 *ctrM2 = ControllerSegM2::getInstance();


	mainCtr->addEvent(START_PRESSED);
	mainCtr->addEvent(STOP_PRESSED);
	mainCtr->addEvent(E_STOP_PRESSED);
	mainCtr->addEvent(E_STOP_RELEASED);
	mainCtr->addEvent(RESET_PRESSED);
	mainCtr->addEvent(RESET_RELEASED);
	mainCtr->addEvent(WP_IS_MISSING);

	// ctrM2->addEvent(WP_IS_COMMING);
	// ctrM2->addEvent(WP_IN_ENGINE_START);
	// ctrM2->addEvent(WP_IN_HEIGHT_M);
	// ctrM2->addEvent(WP_OUT_HEIGHT_M);
	// ctrM2->addEvent(WP_IN_TOLERANCE_R);
	// ctrM2->addEvent(WP_IS_METAL);
	// ctrM2->addEvent(WP_IN_SWITCH);
	// ctrM2->addEvent(WP_OUT_SWITCH);
	// ctrM2->addEvent(WP_OUT_SLIDE);
	// ctrM2->addEvent(WP_OUT_ENGINE_END);

	// ctrM2->addEvent(START_PRESSED);
	// ctrM2->addEvent(STOP_PRESSED);
	// ctrM2->addEvent(E_STOP_PRESSED);
	// ctrM2->addEvent(E_STOP_RELEASED);

	// dispatcher_->registerHandler(ctrM2);
	dispatcher_->registerHandler(mainCtr);
#endif

	dispatcher_->start(NULL);

	dispatcher_->join();

}

void StateTest::shutdown() {
}

