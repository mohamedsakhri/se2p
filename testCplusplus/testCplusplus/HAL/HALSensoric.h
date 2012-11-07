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



using namespace thread;

class HALSensoric:public HAWThread {
public:
	virtual ~HALSensoric();
	static HALSensoric* getInstance();

private:
	HALSensoric(); //!< Constructor
	void initInterrupt(); //!<
	const struct sigevent* ISR (void *arg, int id);

//	PortC portC_;
//	PortB portB_;
	Mutex hal_Sensoric_mutex_;
	static HALSensoric *hal_Sensoric_instance_; //!< Singelton instance for HALSensoric
	struct sigevent event_;
	int isr_coid_;

//protected:
	virtual void execute(void* arg);
	virtual void shutdown();


};

#endif /* HALSENSORIC_H_ */
