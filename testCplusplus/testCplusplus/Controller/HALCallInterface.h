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
	virtual void inEngineStart() = 0;				//!< WP in engine's start
	virtual void outEngineStart() = 0;				//!< WP has left engine's start
	virtual void inHeightMeasurement() = 0;			//!< WP is in height measurement area
	virtual void outHeightMeasurement() = 0;		//!< WP has left height measurement area
	virtual void inToleranceRange() = 0;			//!< WP's height is in tolerance range
	virtual void notInToleranceRange() = 0;			//!< WP's height is not in tolerance range
	virtual void isMetal() = 0;						//!< WP has metal
	virtual void notMetal() = 0;					//!< WP doesn't have metal
	virtual void inSwitch() = 0;					//!< WP is in switch area
	virtual void outSwitch() = 0;					//!< WP has left Switch area
	virtual void switchOpen() = 0;					//!< Switch has been opened
	virtual void switchClosed() = 0;				//!< Switch has been closed
	virtual void inSlide() = 0;						//!< WP is in Slide's barrier (Rutsche)
	virtual void outSlide() = 0;					//!< WP out Slide's light barrier
	virtual void inEngineEnd() = 0;					//!< WP is in engine's end
	virtual void outEngineEnd() = 0;				//!< WP has left engine's end

	virtual void startPressed() = 0;
	virtual void startReleased() = 0;
	virtual void stopPressed() = 0;
	virtual void stopReleased() = 0;
	virtual void resetPressed() = 0;
	virtual void resetReleased() = 0;
	virtual void EStopPressed() = 0;
	virtual void EStopReleased() = 0;

	virtual void isMissing() = 0;
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
	virtual int getControllerId() = 0;

	virtual void addWP2List(WorkPiece wp) =0;
	virtual WorkPiece getLastWP() =0;
	virtual void removeLastWP() =0;
	virtual void passWP2Ctr(HALCallInterface* ctr) =0;
};

#endif //HALCALLINTERFACE_H_
