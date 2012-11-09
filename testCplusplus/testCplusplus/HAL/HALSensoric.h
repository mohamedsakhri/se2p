/*
 * HALSensoric.h
 *
 *  Created on: 07.11.2012
 *      Author: aax877
 */

#ifndef HALSENSORIC_H_
#define HALSENSORIC_H_

#include "HAWThread.h"
#include "Adress.h"
#include "Mutex.h"
#include "stdint.h"

using namespace thread;
const struct sigevent* ISR(void *arg, int id);

class HALSensoric: public HAWThread {
public:
	virtual ~HALSensoric();
	static HALSensoric* getInstance();

private:
	HALSensoric(); //!< Constructor
	void initInterrupt(); //!<
	static Mutex hal_Sensoric_mutex_;
	static HALSensoric *hal_Sensoric_instance_; //!< Singelton instance for HALSensoric
	struct sigevent event_;
	int channel_id_;
	int interrupt_id_;
	uint8_t portC_state_;
	uint8_t portB_state_;

	//protected:
	virtual void execute(void* arg);
	virtual void shutdown();

};

#endif /* HALSENSORIC_H_ */
