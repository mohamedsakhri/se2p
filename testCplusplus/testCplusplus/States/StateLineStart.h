/*
 * StateLineStart.h
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#ifndef STATELINESTART_H_
#define STATELINESTART_H_

#include "IState.h"
#include "ControllerSeg1.h"

using namespace std;

class StateLineStart:public IState {
public:
	StateLineStart();
	virtual ~StateLineStart();

	void inLineStart();
};

class StateWorkPieceCreated:public IState {
public:
	StateWorkPieceCreated();
	virtual ~StateWorkPieceCreated();

	void outLineStart();
};

#endif /* STATELINESTART_H_ */
