/**
 * @file 	HALSensoric.h
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date	Nov 07, 2012
 *
 * This class implements all methods needed to interact with input-hardware.
 *
 */
#ifndef HALSENSORIC_H_
#define HALSENSORIC_H_

#include "HAWThread.h"
#include "Adress.h"
#include "Mutex.h"
#include "stdint.h"


const struct sigevent* ISR(void *arg, int id);

class HALSensoric {
public:
	virtual ~HALSensoric();					//!< Destructor
	/**
	 * @return HALSensoric's instance
	 */
	static HALSensoric* getInstance();		//!< Singleton pattern implementation
	/**
	 * @return channel_id Channel id used in HAL Sensoric
	 */
	int getChannelId();
	/**
	 * @return height Worksspace's height after conversion A/D
	 */
	int calculateHeight();

private:
	HALSensoric();								//!< Constructor
	void initInterrupt();						//!< initialize interrupt's options

	static Mutex hal_Sensoric_mutex_;			//!< Needed for thread-safe implemetation
	static HALSensoric *hal_Sensoric_instance_;	//!< Singelton pattern instance for HALSensoric
	struct sigevent event_;
	int channel_id_;							//!< Channel id
	int interrupt_id_;							//!< Interrupt id

};

#endif /* HALSENSORIC_H_ */
