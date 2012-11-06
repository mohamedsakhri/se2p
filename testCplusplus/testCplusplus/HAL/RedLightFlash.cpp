/*
 * @file 	RedLightFlash.cpp
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	NOV 6, 2012
 *
 *This class is a thread implementation of the flashing red light.
 *the blinking frequence id given as a parameter of the thread function execute.
 *
 */

#include "RedLightFlash.h"

RedLightFlash::RedLightFlash() {
	// TODO Auto-generated constructor stub

}

RedLightFlash::~RedLightFlash() {
	// TODO Auto-generated destructor stub
}


/*
 * flash the red light until the thread stopped
 *
 * @param arg flashing frequence
 */
void RedLightFlash::execute(void* arg){
	HALAktorik *hal_A = HALAktorik::getInstance();
	int* sleeptime = (int*) arg;

	cout << "sleeptime: " << *sleeptime << endl;
	while (!isStopped()){
		hal_A->red_Light_on();
		usleep(*sleeptime);
		hal_A->red_Light_off();
		usleep(*sleeptime);
	}

}

void RedLightFlash::shutdown(){

}
