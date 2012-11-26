/*
 * @file Dispatcher.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date Nov 25, 2012
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
#include <list>

using namespace thread;

//TODO Implement Call-back mechanism : event handler table
// Dispatcher now gets the message from Demultiplexer and has to call the right function
// which must be defined in an event handler table ( not obligatory an array,
// a switch-case on message could do the job too

// Define a pointer to a NON-static member function of HALCallInterface
// which takes no parameters and returns void
typedef void(HALCallInterface::*pt2Func)();
typedef list<HALCallInterface*> ControllersList;	// Define a list of controllers

class Dispatcher : public HAWThread {
public:
	virtual ~Dispatcher();
	/**
	* @return Dispatcher's instance
	*/
	static Dispatcher* getInstance();			//!< For Singleton pattern implementation
	/**
	 * @return Dispatcher's channel ID
	 */
	int getChannelId();						//!< used to get Channel ID from outside this class

	virtual void execute(void* arg);
	virtual void shutdown();


private :
	Dispatcher();
	/**
	 * @param handler Controller to be registered in Dispatcher
	 * @param index   Controller's index in Event handler table
	 */
	void reigisterHandler(int index, HALCallInterface* handler);		//!< Register handler "controller" in Dispatcher
	/**
	 * @param handler Controller to be removed from Dispatcher
	 */
	void removeHandler(HALCallInterface* handler);		//!< Remove handler from Dispatcher
	void initPt2FuncArray();								//!< Initialize an Array of pointer to functions
	int channel_id_;										//!< Dispatcher's channel ID
	int con_id_;											//!< Connection ID to own channel
	static Dispatcher* dispatcher_instance_;				//!< The only dispatcher's instance
	static Mutex dispatcher_mutex_;							//!< Mutex used in Singleton implementation

	Demultiplexer* demultiplexer_;
	pt2Func pt2FuncArray[MESSAGES_NUMBER];					//!< Array of pointers to functions
	ControllersList CTRList;								//!< List of Controllers registered in Dispatcher
};

#endif /* DISPATCHER_H_ */
