/*
 * @file	testCplusplus.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date	Nov 19, 2012
 *
 *
 * This is supposed to be the class which contain main
 */

// TODO Change class's name and do some organization work here !
//

/*
 * macros to run tests
 */
//#define LED_TEST
//#define SWITCH_TEST
//#define MOTOR_TEST
//#define LIGHT_TEST
//#define SERINTERFACE_TEST
//#define SENSORIC_TEST
//#define DISPATCHER_TEST
//#define DEBUG_MUTEX
#define STATE_TEST
//#define TIMER_TEST


#include "HWaccess.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include "SensoricTest.h"
#include "HALSensoric.h"
//#include "Demultiplexer.h"
#include "DispatcherTest.h"
#include "StateTest.h"
#include "TimerTest.h"
#include "Reader.h"
#include "Starter.h"
/*
#include "LEDTest.h"
#include "LightTest.h"
#include "MotorTest.h"
#include "SwitchTest.h"
#include "SerInterfaceTest.h"
*/

using namespace std;
using namespace thread;

int main(int argc, char *argv[]) {
#ifdef SIMULATION
	cout << "Simulation aktiv" << endl;
	cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen."
			<< endl;
	IOaccess_open(); // Baue die Verbindung zur Simulation auf
#endif

//	Starter starter;
//	starter.start(NULL);
//	Reader reader;
//	reader.start(NULL);
//	starter.join();
//	reader.join();

#ifdef STATE_TEST
	StateTest state_test;
	state_test.start(NULL);
	Reader reader;
	reader.start(NULL);
//	SerInterfaceTest *SRtest = new SerInterfaceTest();
	state_test.join();
	reader.join();
#endif

#ifdef TIMER_TEST
	TimerTest timer_test;
	timer_test.start(NULL);
	timer_test.join();
#endif

#ifdef DISPATCHER_TEST
	DispatcherTest dispatcher_test;
	dispatcher_test.start(NULL);
	dispatcher_test.join();
#endif

#ifdef SENSORIC_TEST
	SensoricTest sensoric_test ;
	sensoric_test.start(NULL);
#endif

#ifdef LED_TEST
	LEDTest ledTest;
	ledTest.start(NULL);
#endif

#ifdef LIGHT_TEST
	LightTest lightTest;
	lightTest.start(NULL);
#endif

#ifdef MOTOR_TEST
	MotorTest motorTest;
	motorTest.start(NULL);
#endif

#ifdef SWITCH_TEST
	SwitchTest switchTest;
	switchTest.start(NULL);
#endif

#ifdef SERINTERFACE_TEST
	cout << "testCplusplus Serial Interface" << endl;
	SerInterfaceTest *SRtest = new SerInterfaceTest();
#endif

#ifdef LED_TEST
	ledTest.join();
#endif

#ifdef LIGHT_TEST
	lightTest.join();
#endif

#ifdef MOTOR_TEST
	motorTest.join();
#endif

#ifdef SWITCH_TEST
	switchTest.join();
#endif

#ifdef SENSORIC_TEST
	sensoric_test.join();
#endif

#ifdef SIMULATION
	IOaccess_close(); // Schliesse die Verbindung zur Simulation
#endif
}
