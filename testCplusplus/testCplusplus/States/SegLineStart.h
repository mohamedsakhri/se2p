/*
 * @file	SegLineStart.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 1
 *
 */

#ifndef SEGLINESTART_H_
#define SEGLINESTART_H_

#include "IState.h"
#include "ControllerSeg1.h"

using namespace std;

/*
 *
 */
class StateLineStart:public IState {
public:
	StateLineStart();
	virtual ~StateLineStart();

	void inLineStart();
};

/*
 *
 */
class StateWorkPieceCreated:public IState {
public:
	StateWorkPieceCreated();
	virtual ~StateWorkPieceCreated();

	void outLineStart();
};

#endif /* SEGLINESTART_H_ */
