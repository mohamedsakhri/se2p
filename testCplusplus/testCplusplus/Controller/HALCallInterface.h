/*
 * @file HALCallInterface.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date Nov 26, 2012
 *
 *	This class is an abstract class, which contains Sensoric's functions' prototypes
 */
#ifndef HALCALLINTERFACE_H_
#define HALCALLINTERFACE_H_

class HALCallInterface {
public :
	virtual void inEngineStart() = 0;
	virtual void outEngineStart() = 0;
	virtual void inHeightMeasurement() = 0;
	virtual void outHeightMeasurement() = 0;
	virtual void inToleranceRange() = 0;
	virtual void notInToleranceRange() = 0;
	virtual void isMetal() = 0;
	virtual void notMetal() = 0;
	virtual void inSwitch() = 0;
	virtual void outSwitch() = 0;
	virtual void inSlide() = 0;
	virtual void outSlide() = 0;
	virtual void inEngineEnd() = 0;
	virtual void outEngineEnd() = 0;
	virtual void startPressed() = 0;
	virtual void startReleased() = 0;
	virtual void stopPressed() = 0;
	virtual void stopReleased() = 0;
	virtual void resetPressed() = 0;
	virtual void resetReleased() = 0;
	virtual void EStopPressed() = 0;
	virtual void EStopReleased() = 0;

};

#endif //HALCALLINTERFACE_H_
