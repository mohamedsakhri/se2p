/*
 * MyThread.cpp
 *
 *  Created on: 11.10.2012
 *      Author: aar740
 */

// Die Header Datei HWaccess.h steuert den Zugriff auf die HW bzw. Simulation
// Sie muss in jeder Datei stehen, die auf die HW zugreift


#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <errno.h>
#include "MyThread.h"
#include "HALAktorik.h"

using namespace thread;
class HALAktorik;

MyThread::MyThread() {
	// TODO Auto-generated constructor stub
}

MyThread::~MyThread() {
	// TODO Auto-generated destructor stub
}

void MyThread::shutdown() {
	cout << "Test finished" << endl;
}

void MyThread::execute(void *arg) {
	// This returns an error which is driving me crazy!!
	// still working on itS
	//HALAktorik *hal_A = new HALAktorik();
	HALAktorik *hal_A = HALAktorik::getInstance();

	while (!isStopped()) {

//		hal_A->red_Light_quick();

//		hal_A->red_Light_off();
	//	sleep(1);

		hal_A->green_Light_off();
		hal_A->red_Light_on();
		sleep(1);
		hal_A->red_Light_off();
		sleep(1);


		/*
		hal_A->open_Switch();
		sleep(3);

		hal_A->close_Switch();
		sleep(3);
*/
/*
		out8(DIGITAL_CARD_CROUP0_PORTA, 0x00);
		sleep(3);

		hal_A->motor_on();
		cout << "Motor on " << endl;

		hal_A->red_Light_on();
		cout << "Red light on " << endl;
		sleep(1);

		hal_A->red_Light_off();
		cout << "Red light off " << endl;
		sleep(1);

		hal_A->yellow_Light_on();
		cout << "Yellow light on " << endl;
		sleep(1);

		hal_A->yellow_Light_off();
		cout << "Yellow light off " << endl;
		sleep(1);

		hal_A->green_Light_on();
		cout << "Green light on " << endl;
		sleep(1);

		hal_A->green_Light_off();
		cout << "Green light off " << endl;
		sleep(1);

		hal_A->open_Switch();
		cout << "Switch open" << endl;
		sleep(1);

		hal_A->close_Switch();
		hal_A->motor_off();
		cout << "Motor off " << endl;


*/
	}
	hal_A->red_Light_off();
			cout << "Red light off " << endl;
			sleep(1);

}

