/*
 * @file :	WorkPiece.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	30.11.2012
 *
 * This class represents a Workpiece.
 */

#ifndef WORKPIECE_H_
#define WORKPIECE_H_

#include "Timer.h"
#include "Demultiplexer.h"
#include "Messages.h"
#include "Constants.h"

class WorkPiece {
public:
	WorkPiece();
	virtual ~WorkPiece();

	/**
	* @return true if Worpiece's in tolerance range
	*/
	bool getIs_inTolleranceRange();
	/**
	 * @param isinTolleranceRange Set Tolerance range to true or false
	 */
	void setIs_inTolleranceRange(bool isinTolleranceRange);
	/**
	 * @return true if workpiece's metal
	 */
    bool getIs_Metal();
	/**
	 * @param isMetal Set is_Metal_ to true or false
	 */
    void setIs_Metal(bool isMetal);
    /**
     * @return  true if workpiece's drill
     */
    bool getHas_Drill();
    /**
     * @param hasDrill Set has_Drill to true or false
     */
    void setHas_Drill(bool hasDrill);
    /**
     * @return Timer associated to the workpiece
     */
    Timer* getTimer();

    static int counter;

private:
    Timer* timer_;					//!< Timer to be used to control the workpiece status according to time
	bool is_Metal_;					//!< Indicates workpiece's metal status
	bool is_inTolleranceRange_;		//!< Indicates workpiece's tolerance range status
	bool has_Drill_;				//!< Indicates workpiece's drill drill
};

#endif /* WORKPIECE_H_ */
