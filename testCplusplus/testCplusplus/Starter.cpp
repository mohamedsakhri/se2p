/*
 * @file Configurator.cpp
 *
 * @author Mahmoud Dariti
 * @author Mohamed Sakhri
 *
 * @date Nov 11, 2012
 *
 * This class is used to start the configuration of machine.
 */

#include "Starter.h"
#include "Constants.h"

#define MACHINE_1
//#define MACHINE_2

#define DEBUG_


/**
 * Constructor has nothing to do.
 */
Starter::Starter() {
#ifdef DEBUG_
	cout << "Starter :: Constructor" << endl;
#endif
}

/**
 * Destructor has nothing to do.
 */
Starter::~Starter() {

}

/**
 * Create main controller and register it by dispatcher with its events.
 */
void Starter::execute(void *arg) {
#ifdef DEBUG_
	cout << "Starter  started" << endl;
#endif

#ifdef MACHINE_1

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

	Dispatcher::getInstance()->registerHandler(mainCtr);

#endif

#ifdef MACHINE_2
	MainController *mainCtr = MainController::getInstance();

	mainCtr->addEvent(START_PRESSED);
	mainCtr->addEvent(STOP_PRESSED);
	mainCtr->addEvent(E_STOP_PRESSED);
	mainCtr->addEvent(E_STOP_RELEASED);
	mainCtr->addEvent(RESET_PRESSED);
	mainCtr->addEvent(RESET_RELEASED);
	mainCtr->addEvent(WP_IS_MISSING);
	mainCtr->addEvent(WP_IS_STRANGER);
	mainCtr->addEvent(SLIDE_FULL);
	mainCtr->addEvent(SLIDE_EMPTY);

	dispatcher_->registerHandler(mainCtr);
#endif

	Dispatcher::getInstance()->start(NULL);
	Dispatcher::getInstance()->join();
}

/**
 * shutdown has nothing to do.
 */
void Starter::shutdown() {

}

