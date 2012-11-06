/**
 * @file 	RedLightFlash.h
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	NOV 6, 2012
 *
 *
 *This class is a thread implementation of the flashing red light.
 */

#ifndef REDLIGHTFLASH_H_
#define REDLIGHTFLASH_H_

#include "HAWThread.h"
#include "Constants.h"
#include "HALAktorik.h"

class RedLightFlash: public thread::HAWThread {
public:
	RedLightFlash();			//!< Constructor
	virtual ~RedLightFlash();	//!< Destructor
private:
	virtual void execute(void*arg);	//!< function executed when the thread starts
 	virtual void shutdown();
};

#endif /* REDLIGHTFLASH_H_ */
