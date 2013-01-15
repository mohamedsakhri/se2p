/*
 * @file IState.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date Nov 30, 2012
 *
 *	This class is virtual class, which contains Sensoric's functions' prototypes
 */
#ifndef ISTATE_H_
#define ISTATE_H_

//#include "HALCallInterface.h"

#include <iostream>
#include "HALAktorik.h"
#include "WorkPiece.h"
#include "RedLightFlash.h"

class IState {
public :
	virtual void inLineStart(){};				//!< WP in Line's start
	virtual void outLineStart(){};				//!< WP has left Line's start
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
	virtual void inLineEnd(){};					//!< WP is in Line's end
	virtual void outLineEnd(){};					//!< WP has left Line's end

	virtual void startPressed(){};
	virtual void startReleased(){};
	virtual void stopPressed(){};
	virtual void stopReleased(){};
	virtual void resetPressed(){};
	virtual void resetReleased(){};
	virtual void EStopPressed(){};
	virtual void EStopReleased(){};

	//Communication between Machine1 and Machine2
	virtual void wpIsComming(){};				//!< WP has left machine 1 and comming to machine 2
	virtual void machine2IsReady(){};			//!< Machine 2 has passed from status busy to ready
	virtual void messageReceived(){};

	//Error handling
	virtual void initState(){};
	virtual void runningMachine1(){};
	virtual void runningMchine2(){};
	virtual void stop(){};
	virtual void errorHandling(){};
	virtual void emergency(){};
	virtual void isMissing(){};
	virtual void timeOutError() {};
	virtual void errorFixed(){};
	virtual void slideFull(){};
	virtual void slideErrorFixed(){};
	virtual void turningErrorHandling(){};

};

#endif //ISTATE_H_
