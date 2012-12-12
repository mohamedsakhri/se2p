/*
 * @file 	ControllerSeg3.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * This class represents the controller of the third segment which controls the switch area
 */

#ifndef CONTROLLERSEG3_H_
#define CONTROLLERSEG3_H_

#include <iostream.h>
#include "HALCallInterface.h"
//#include <vector>
#include "Dispatcher.h"
#include "Demultiplexer.h"
//#include "IState.h"
#include "WorkPiece.h"
#include "WaitingSwitch.h"
#include "Mutex.h"

class ControllerSeg3: public HALCallInterface {
public:
	static ControllerSeg3* getInstance();

	void inSwitch();
	void outSwitch();

	//TODO COMMENT
		// Error's handling
		int sendMsg2Dispatcher(int message);
		void init();

		virtual ~ControllerSeg3();

		void addEvent(int event_index);
		vector<int> getEvents();

		//FIFO Control
		void addWP2List(WorkPiece* wp);
		WorkPiece* getLastWP();
		void removeLastWP();
		void passWP2Ctr();

	private:
		ControllerSeg3();

//		vector<int> events_list_;		//!< Event's list the controller is/want to registered to
//		vector<WorkPiece*> wp_list_;		//!< fifo list for workpieces
//		int con_id_;
//		IState* state_;
		static ControllerSeg3* controllerSeg3_instance_ ;
		static Mutex controllerSeg3_mutex_; 		//!< Mutex for thread-safe implementation


	};

#endif /* CONTROLLERSEG2_H_ */
