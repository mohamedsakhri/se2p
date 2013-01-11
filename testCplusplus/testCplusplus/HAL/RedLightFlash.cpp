/*
 * @file 	LightFlash.cpp
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date	NOV 6, 2012
 *
 *	This class is a thread implementation of the flashing red light.
 *	the blinking frequence id given as a parameter of the thread function execute.
 *
 */

#include "RedLightFlash.h"
//#define DEBUG_

RedLightFlash* RedLightFlash::light_flash_instance_ = NULL;
Mutex RedLightFlash::light_flash_mutex_ = Mutex();


RedLightFlash::RedLightFlash() {
	is_flashing_ = true;
}

RedLightFlash::~RedLightFlash() {
	// TODO Auto-generated destructor stub
}

RedLightFlash* RedLightFlash::getInstance() {
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
			perror("ThreadCtl access failed\n");
			return NULL;
		}

	if (!light_flash_instance_) {
		light_flash_mutex_.lock();
		if (!light_flash_instance_) {
			light_flash_instance_ = new RedLightFlash;
		}
		light_flash_mutex_.unlock();
	}


	return light_flash_instance_;
}

/*
 * start the flashing thread
 */
void RedLightFlash::flash(int light, int sleeptime){
#ifdef DEBUG_
	cout << "LightFlash :: flash " << endl;

#endif

	this->sleeptime_ = sleeptime;
	this->light_ = light;
	if (!is_flashing_) {
		this->cont();
	} else {
		this->start(NULL);
	}
}


/*
 * flash the red light until the thread stopped
 *
 */
void RedLightFlash::execute(void* arg){
#ifdef DEBUG_
	cout << "sleeptime: " << sleeptime_ << endl;
	cout << "light: " << light_ << endl;
#endif
//	HALAktorik *hal_A = HALAktorik::getInstance();
	if (light_ == RED){
		while (!isStopped()){
			HALAktorik::getInstance()->red_Light_on();
			usleep(sleeptime_);
			HALAktorik::getInstance()->red_Light_off();
			usleep(sleeptime_);
		}
	}
}
void RedLightFlash::stopFlashing(){
	HALAktorik::getInstance()->red_Light_off();
	is_flashing_ = false;
	hold();

}

void RedLightFlash::shutdown(){

}
