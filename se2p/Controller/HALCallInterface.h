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

#include <iostream.h>
#include "Mutex.h"
#include "Demultiplexer.h"
#include <vector>
#include "WorkPiece.h"
#include "IState.h"
#include "Constants.h"
#include "Sender.h"

class HALCallInterface {
public :											//WP = Workpiece
	virtual void inLineStart() {};				//!< WP in line's start
	virtual void outLineStart(){};				//!< WP has left line's start
	virtual void inHeightMeasurement(){};		//!< WP is in height measurement area
	virtual void outHeightMeasurement(){};		//!< WP has left height measurement area
	virtual void inToleranceRange(){};			//!< WP's height is in tolerance range
	virtual void notInToleranceRange(){};		//!< WP's height is not in tolerance range
	virtual void isMetal(){};						//!< WP has metal
	virtual void notMetal(){};					//!< WP doesn't have metal
	virtual void inSwitch(){};					//!< WP is in switch area
	virtual void outSwitch(){};					//!< WP has left Switch area
	virtual void switchOpen(){};					//!< Switch has been opened
	virtual void switchClosed(){};				//!< Switch has been closed
	virtual void inSlide(){};						//!< WP is in Slide's barrier (Rutsche)
	virtual void outSlide(){};					//!< WP out Slide's light barrier
	virtual void inLineEnd(){};					//!< WP is in line's end
	virtual void outLineEnd(){};					//!< WP has left line's end

	virtual void startPressed(){};				//!< Start button pressed
	virtual void startReleased(){};				//!< Start button released
	virtual void stopPressed(){};				//!< Stop button pressed
	virtual void stopReleased(){};				//!< Stop button released
	virtual void resetPressed(){};				//!< Reset button pressed
	virtual void resetReleased(){};				//!< Reset button released
	virtual void EStopPressed(){};				//!< E-Stop button pressed
	virtual void EStopReleased(){};				//!< E-Stop button pulled out
	virtual void EStopPressedOther(){};			//!< E-Stop button pressed on the other machine
	virtual void EStopReleasedOther(){};			//!< E-Stop button released on the other machine

	/*
	 * Error Handling
	 */
	virtual void isMissing(){};					//!< WP is missing
	virtual void isStranger(){};					//!< WP is stranger
	virtual void slideFull(){};					//!< Slide is full
	virtual void slideEmpty(){};					//!< Slide has become empty
	virtual void notTurned(){};					//!< WP has not put back in machine1's end



	/*
	 * Communication between Machine1 and machine2
	 */
	virtual void wpIsComming(){};				//!< Notify machine2 that a WP is coming
	virtual void wpHasArrived(){};				//!< Notify machine1 that a WP has arrived
	virtual void m2isReady(){};					//!< Notify machine1 when machine2 has become ready
	virtual void m2isBusy(){};					//!< Notify machine1 when machine2 has become ready

	/*
	 * Reset controller
	 */

	virtual void reset(){};

	/**
	 * @param even_index Id of event_ the controller want to register to
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

	/**
	 * @return first WP in Fifo
	 */
	virtual WorkPiece* getFirstWP() {
		return wp_list_.front();
	}

	/**
	 * Remove first element from Fifo
	 */
	virtual void removeFirsttWP() {
		if (!wp_list_.empty()){
			wp_list_.erase(wp_list_.begin());
			}
		else{
			cout << "Fifo is empty " << endl;
		}
	};

	virtual vector<WorkPiece*> getWPList() {
		return wp_list_;
	}

	virtual bool isFifoEmpty() {
		return wp_list_.empty();
	};

	virtual void passWP2Ctr() = 0;	//!< Pass WP to next controller

	/**
	 * @return ctr_id Controller Id
	 */
	virtual int getControllerId(){
		return ctr_id_;
	}

	/**
	 * @return If machine is motor is running
	 */
	virtual bool isRunning() {
		return isRunning_;
	}

	/**
	 * @param isRunning true if motor is running
	 */
	void setIsRunning(bool isRunning)
	{
		isRunning_ = isRunning;
	}

protected :
	vector<int> events_list_;			//!< Event's list the controller is/want to registered to
	vector<WorkPiece*> wp_list_;		//!< Fifo as list of pointers to workpieces
	int con_id_;						//!< Connection Id to Demultiplexer Channel
	int ctr_id_;						//!< Id of each controller
	IState* state_;						//!< State machine
	bool isRunning_;					//!< If motor running or not.
};

#endif //HALCALLINTERFACE_H_
