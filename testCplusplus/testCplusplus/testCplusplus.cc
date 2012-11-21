/*
 * Kleines Beispielprogramm fuer den Zugriff auf die Festo Simulationsumgebung
 * der Transferstrecke und die Transferstrecke selbst.
 *
 * Voraussetzungen:
 *      - Die Bibliotheken und Header Files mussen in in der Entwicklungs-
 *        umgebung eingepfegt sein.
 *
 *       - Die Bibliothek ioaccess muss im Projekt eingebunden sein via
 *         Project->Properties : QNX C/C++ Project : Linker : Extra libraries
 */
// Die Header Datei HWaccess.h steuert den Zugriff auf die HW bzw. Simulation
// Sie muss in jeder Datei stehen, die auf die HW zugreift

/*
 * macros to run tests
 */
//#define LED_TEST
//#define SWITCH_TEST
//#define MOTOR_TEST
//#define LIGHT_TEST
//#define SER_INTERFACE_TEST
//#define SENSORIC_TEST
//#define DEBUG_MUTEX
#define DEBUX_


#include "HWaccess.h"
#include "MyThread.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include "SensoricTest.h"

/*
#include "LEDTest.h"
#include "LightTest.h"
#include "MotorTest.h"
#include "SwitchTest.h"
#include "SerInterfaceTest.h"
#include "HALSensoric.h"
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

	HALSensoric *hal_sensorik = HALSensoric::getInstance();
	hal_sensorik->start(NULL);

	SensoricTest sensorik_test ;
	sensorik_test.start(NULL);
	sensorik_test.join();


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
