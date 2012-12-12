/*
 * @file HALCallInterface.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date Nov 26, 2012
 *
 *	This class is virtual class, which contains Sensoric's functions' prototypes
 */
#ifndef HALCALLINTERFACE_H_
#define HALCALLINTERFACE_H_

#include <vector>
#include "WorkPiece.h"
#include "IState.h"

//class WorkPiece;

class HALCallInterface {
public :											//WP = Workpiece
	virtual void inEngineStart() {};				//!< WP in engine's start
	virtual void outEngineStart(){};				//!< WP has left engine's start
	virtual void inHeightMeasurement(){};			//!< WP is in height measurement area
	virtual void outHeightMeasurement(){};		//!< WP has left height measurement area
	virtual void inToleranceRange(){};			//!< WP's height is in tolerance range
	virtual void notInToleranceRange(){};			//!< WP's height is not in tolerance range
	virtual void isMetal(){};						//!< WP has metal
	virtual void notMetal(){};					//!< WP doesn't have metal
	virtual void inSwitch(){};					//!< WP is in switch area
	virtual void outSwitch(){};					//!< WP has left Switch area
	virtual void switchOpen(){};					//!< Switch has been opened
	virtual void switchClosed(){};				//!< Switch has been closed
	virtual void inSlide(){};						//!< WP is in Slide's barrier (Rutsche)
	virtual void outSlide(){};					//!< WP out Slide's light barrier
	virtual void inEngineEnd(){};				//!< WP is in engine's end
	virtual void outEngineEnd(){};				//!< WP has left engine's end

	virtual void startPressed(){};
	virtual void startReleased(){};
	virtual void stopPressed(){};
	virtual void stopReleased(){};
	virtual void resetPressed(){};
	virtual void resetReleased(){};
	virtual void EStopPressed(){};
	virtual void EStopReleased(){};

	virtual void isMissing(){};
	/**
	 * @param even_index Id of event the controller want to register to
	 */
	virtual void addEvent(int event_index) {
		events_list_.push_back(event_index);
	};
	/**
	 * @return List of events the controller is registered to
	 */
	virtual vector<int> getEvents() {
		return events_list_;
	}

	/**
	 * @return controller id
	 */

	virtual void addWP2List(WorkPiece* wp) {
		wp_list_.push_back(wp);
	};
	virtual WorkPiece* getLastWP() {
		return wp_list_.front();
	}

	virtual void removeLastWP() {
		if (!wp_list_.empty()){
			wp_list_.erase(wp_list_.begin());
			}
		else{
			cout << "Fifo is empty " << endl;
		}
	};
	virtual void passWP2Ctr(){};
protected :
	vector<int> events_list_;		//!< Event's list the controller is/want to registered to
	vector<WorkPiece*> wp_list_;		//!< fifo list for workpieces
	int con_id_;
	IState* state_;
};

#endif //HALCALLINTERFACE_H_
