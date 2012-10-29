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

#include "HWaccess.h"
#include "MyThread.h"
#include <cstdlib>
#include <iostream>
#include<unistd.h>
#include <errno.h>


using namespace std;
using namespace thread;

int main(int argc, char *argv[]) {
#ifdef SIMULATION
	cout << "Simulation aktiv" << endl;
	cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen."
			<< endl;
	IOaccess_open(); // Baue die Verbindung zur Simulation auf
#endif

	MyThread thr;
	thr.start(NULL);
	sleep(10);
	thr.stop();
	thr.join();

#ifdef SIMULATION
	IOaccess_close(); // Schliesse die Verbindung zur Simulation
#endif
}
