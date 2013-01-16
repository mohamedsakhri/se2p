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

	MainController *mainCtr = MainController::getInstance();

	mainCtr->addEvent(START_PRESSED);
	mainCtr->addEvent(START_RELEASED);
	mainCtr->addEvent(STOP_PRESSED);
	mainCtr->addEvent(E_STOP_PRESSED);
	mainCtr->addEvent(E_STOP_RELEASED);
	mainCtr->addEvent(E_STOP_PRESSED_OTHER);
	mainCtr->addEvent(E_STOP_RELEASED_OTHER);
	mainCtr->addEvent(RESET_PRESSED);
	mainCtr->addEvent(RESET_RELEASED);
	mainCtr->addEvent(WP_IS_MISSING);
	mainCtr->addEvent(WP_IS_STRANGER);
	mainCtr->addEvent(SLIDE_FULL);
	mainCtr->addEvent(SLIDE_EMPTY);
	mainCtr->addEvent(WP_NOT_TURNED);

	dispatcher_->registerHandler(mainCtr);

#endif

#ifdef TEST_MACHINE_2
	MainController *mainCtr = MainController::getInstance();

	mainCtr->addEvent(START_PRESSED);
	mainCtr->addEvent(STOP_PRESSED);
	mainCtr->addEvent(E_STOP_PRESSED);
	mainCtr->addEvent(E_STOP_RELEASED);
	mainCtr->addEvent(E_STOP_PRESSED_OTHER);
	mainCtr->addEvent(E_STOP_RELEASED_OTHER);
	mainCtr->addEvent(RESET_PRESSED);
	mainCtr->addEvent(RESET_RELEASED);
	mainCtr->addEvent(WP_IS_MISSING);
	mainCtr->addEvent(WP_IS_STRANGER);
	mainCtr->addEvent(SLIDE_FULL);
	mainCtr->addEvent(SLIDE_EMPTY);

	dispatcher_->registerHandler(mainCtr);
#endif

	dispatcher_->start(NULL);
	dispatcher_->join();

}

void StateTest::shutdown() {
}

