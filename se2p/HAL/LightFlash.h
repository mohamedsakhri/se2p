/**
 * @file 	LightFlash.h
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date	NOV 6, 2012
 *
 *
 *This class is a thread implementation of the flashing red light.
 */

#ifndef LIGHTFLASH_H_
#define LIGHTFLASH_H_

#include "HAWThread.h"
#include "Constants.h"
#include "HALAktorik.h"
#include "Mutex.h"

class LightFlash: public thread::HAWThread {
public:
	static LightFlash *getInstance();
	virtual ~LightFlash();	//!< Destructor

	void flash(int light, int sleeptime);
	void stopFlashing();

private:
	LightFlash();			//!< Constructor
	void execute(void*arg);	//!< function executed when the thread starts
	void shutdown();


 	int sleeptime_;
 	int light_;
 	bool is_flashing_;

 	static LightFlash * light_flash_instance_;
 	static Mutex light_flash_mutex_;
};

#endif /* LIGHTFLASH_H_ */
