/*
 * @file	Controller.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	Nov 26, 2012
 *
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <iostream.h>
#include "HALCallInterface.h"
//#include <vector>
#include "HALAktorik.h"
#include "Dispatcher.h"
#include "Demultiplexer.h"
#include "IState.h"
#include "WorkPiece.h"
#include "StateHeight.h"
#include "Mutex.h"

class ControllerSeg2: public HALCallInterface {
public:
	ControllerSeg2* getInstance();

	void inHeightMeasurement();
	void outHeightMeasurement();
	void inToleranceRange();
	void notInToleranceRange();

	//TODO COMMENT
		// Error's handling
		int sendMsg2Dispatcher(int message);
		void init();

		virtual ~ControllerSeg2();

		void addEvent(int event_index);
		vector<int> getEvents();

		//FIFO Control
		void addWP2List(WorkPiece wp);
		WorkPiece getLastWP();
		void removeLastWP();
		void passWP2Ctr(HALCallInterface* ctr);

	private:
		ControllerSeg2();

		vector<int> events_list_;		//!< Event's list the controller is/want to registered to
		vector<WorkPiece> wp_list_;		//!< fifo list for workpieces
		int con_id_;
		IState* state_;
		static ControllerSeg2* controllerSeg2_instance_ ;
		static Mutex controllerSeg2_mutex_; 		//!< Mutex for thread-safe implementation


	};

#endif /* CONTROLLER_H_ */
