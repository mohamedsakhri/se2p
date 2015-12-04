/*
 * @file	SegSlide.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 4
 *
 */

#ifndef SEGSLIDE_H_
#define SEGSLIDE_H_

#include "IState.h"
#include "ControllerSeg1.h"
#include "ControllerSeg2.h"
#include "ControllerSeg3.h"
#include "ControllerSeg4.h"
#include "ControllerSeg5.h"

using namespace std;

/*
 *
 */
class SlideWait: public IState {
public:
	SlideWait();
	virtual ~SlideWait();

	void inSlide();
};

/*
 *
 */
class InSlide: public IState {
public:
	InSlide();
	virtual ~InSlide();

	void outSlide();
};


#endif /*SEGSLIDE_H_ */
