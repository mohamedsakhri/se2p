/*
 * StateLineStart.h
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#ifndef STATELINESTART_H_
#define STATELINESTART_H_

#include "HALAktorik.h"
#include "IState.h"
#include <iostream.h>
#include "Controller.h"

using namespace std;

class StateLineStart:public IState {
public:
	StateLineStart();
	virtual ~StateLineStart();

	void inLineStart();
private:
	HALAktorik* hal_aktorik_;
};

class StateWorkPieceCreated:public IState {
public:
	StateWorkPieceCreated();
	virtual ~StateWorkPieceCreated();

	void outLineStart();
private:
	HALAktorik* hal_aktorik_;
};

#endif /* STATELINESTART_H_ */
