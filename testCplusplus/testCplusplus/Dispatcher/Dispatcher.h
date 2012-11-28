/*
 * @file Dispatcher.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date 	Nov 25, 2012
 *
 *
 *	This Class implements the Dispatcher's design pattern.
 *	Dispatcher gets messages from Demultiplexer ( and Controller )
 *	and execute a call-back to the right event handler(function) registred in its event handler table
 */
#ifndef DISPATCHER_H_
#define DISPATCHER_H_


#include "HAWThread.h"
#include "Mutex.h"
#include "Messages.h"
#include "Adress.h"
#include "Demultiplexer.h"
#include "HALCallInterface.h"
#include <vector>

using namespace thread;

// Define a pointer to a NON-static member function of HALCallInterface
// which takes no parameters and returns void
typedef void(HALCallInterface::*pt2Func)();

// Define a list of pointer to controllers
typedef vector<HALCallInterface*> ControllersList;

class Dispatcher : public HAWThread {
public:
	virtual ~Dispatcher();
	/**
	* @return Dispatcher's instance
	*/
	static Dispatcher* getInstance();						//!< For Singleton pattern implementation
	/**
	 * @param handler Controller to be registered in Dispatcher
	 */
	void registerHandler(HALCallInterface* handler);		//!< Register handler in Dispatcher's list
	/**
	 * @param handler Controller to be removed from Dispatcher
	 */
	void removeHandler(HALCallInterface* handler);		//!< Remove handler from Dispatcher

	void execute(void* arg);
	void shutdown();


private :
	Dispatcher();

	void initPt2FuncArray();								//!< Initialize an Array of pointer to functions
	int con_id_;											//!< Connection ID to own channel
	static Dispatcher* dispatcher_instance_;				//!< The only dispatcher's instance
	static Mutex dispatcher_mutex_;							//!< Mutex used in Singleton implementation

	Demultiplexer* demultiplexer_;
	pt2Func pt2FuncArray[MESSAGES_NUMBER];					//!< Array of pointers to functions
	// MESSAGES_NUMBERS = Number of events. See Messages.h
	ControllersList CTRList[MESSAGES_NUMBER];				//!< Array of Controllers' list for each event
};

#endif /* DISPATCHER_H_ */
