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

//class WorkPiece;

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

	virtual void startPressed(){
		HALAktorik::getInstance()->motor_on();
		HALAktorik::getInstance()->red_Light_off();
		HALAktorik::getInstance()->green_Light_on();
		HALAktorik::getInstance()->yellow_Light_off();
		HALAktorik::getInstance()->Start_LED_on();
	};
	virtual void startReleased(){};
	virtual void stopPressed(){
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->red_Light_off();
		HALAktorik::getInstance()->green_Light_off();
		HALAktorik::getInstance()->yellow_Light_off();
		HALAktorik::getInstance()->Start_LED_off();
	};
	virtual void stopReleased(){};
	virtual void resetPressed(){};
	virtual void resetReleased(){};
	virtual void EStopPressed(){
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->Start_LED_off();
	};
	virtual void EStopReleased(){};

	virtual void isMissing(){};
	virtual void isStranger(){};

	/*
	 * Communication between Machine1 and machine2
	 */
	virtual void m2isReady(){};
	virtual void m2isBusy(){};

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

protected :
	vector<int> events_list_;			//!< Event's list the controller is/want to registered to
	vector<WorkPiece*> wp_list_;		//!< Fifo as list of pointers to workpieces
	int con_id_;						//!< Connection Id to Demultiplexer Channel
	int ctr_id_;
	IState* state_;						//!< State machine
	//TODO det Sender as singelton
	Sender* sender_;
};

#endif //HALCALLINTERFACE_H_
