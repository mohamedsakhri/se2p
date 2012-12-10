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
//#include "WorkPiece.h"

class WorkPiece;

class HALCallInterface {
public :											//WP = Workpiece
	virtual void inEngineStart();				//!< WP in engine's start
	virtual void outEngineStart();				//!< WP has left engine's start
	virtual void inHeightMeasurement();			//!< WP is in height measurement area
	virtual void outHeightMeasurement();		//!< WP has left height measurement area
	virtual void inToleranceRange();			//!< WP's height is in tolerance range
	virtual void notInToleranceRange();			//!< WP's height is not in tolerance range
	virtual void isMetal();						//!< WP has metal
	virtual void notMetal();					//!< WP doesn't have metal
	virtual void inSwitch();					//!< WP is in switch area
	virtual void outSwitch();					//!< WP has left Switch area
	virtual void switchOpen();					//!< Switch has been opened
	virtual void switchClosed();				//!< Switch has been closed
	virtual void inSlide();						//!< WP is in Slide's barrier (Rutsche)
	virtual void outSlide();					//!< WP out Slide's light barrier
	virtual void inEngineEnd();					//!< WP is in engine's end
	virtual void outEngineEnd();//!< WP has left engine's end

	virtual void startPressed();
	virtual void startReleased();
	virtual void stopPressed();
	virtual void stopReleased();
	virtual void resetPressed();
	virtual void resetReleased();
	virtual void EStopPressed();
	virtual void EStopReleased();

	virtual void isMissing();
	/**
	 * @param even_index Id of event the controller want to register to
	 */
	virtual void addEvent(int event_index) = 0;
	/**
	 * @return List of events the controller is registered to
	 */
	virtual vector<int> getEvents() = 0;

	/**
	 * @return controller id
	 */

	virtual void addWP2List(WorkPiece wp) =0;
	virtual WorkPiece getLastWP() =0;
	virtual void removeLastWP() =0;
	virtual void passWP2Ctr() =0;
};

#endif //HALCALLINTERFACE_H_
