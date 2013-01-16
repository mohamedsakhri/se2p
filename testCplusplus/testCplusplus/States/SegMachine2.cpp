/*
 * StateMachine2.cpp
 *
 * Created on: 14.12.2012
 * Author: aax844
 */

#include "SegMachine2.h"
#define DEBUG_

/************************************************************************************
 	 	 	 	 	 	 	 	 WaitForLineStart

 ************************************************************************************/
/**
 * Constructor
 */
WaitForLineStart::WaitForLineStart() {
#ifdef DEBUG_
	cout << "WaitForLineStart :: Constructor" << endl;
#endif
}

/**
 * Destructor has nothing to do
 */
WaitForLineStart::~WaitForLineStart() {

}

/**
 * Message received from machine 1 that a Worpiece is comming
 */
void WaitForLineStart::wpIsComming() {
	WorkPiece* wp = new WorkPiece();
	ControllerSegM2::getInstance()->addWP2List(wp);

//	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->setNewTime(THREE_SEC, NULL_MSEC);
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->start(THREE_SEC, NULL_MSEC);

	HALAktorik::getInstance()->motor_on();
	MainController::getInstance()->setIsRunning(true);


	Sender::getInstance()->send(MACHINE2_IS_BUSY);
	new (this) WpIsComming();
}

/************************************************************************************
 	 	 	 	 	 	 	 	 WpIsComming

 ************************************************************************************/
/**
 * Constructor does nothing
 */
WpIsComming::WpIsComming() {
#ifdef DEBUG_
	cout << "WpIsComming :: Constructor" << endl;
#endif
}

/**
 * Destructor does nothing
 */
WpIsComming::~WpIsComming() {
}

/**
 * Wp in line start :
 * Notify machine1 and goes to new state
 */
void WpIsComming::inLineStart() {
	Sender::getInstance()->send(WP_HAS_ARRIVED);
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->stop();
//	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->setNewTime(NINE_SEC, NULL_MSEC);
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->start(NINE_SEC, NULL_MSEC);
	new (this) WaitForHeightM2();
}

/************************************************************************************
 	 	 	 	 	 	 	 	 WaitForHeightM2

 ************************************************************************************/
/**
 * Constructor does nothing
 */
WaitForHeightM2::WaitForHeightM2() {
#ifdef DEBUG_
	cout << "WaitForHeightM2 :: Constructor" << endl;
#endif
}

/**
 * Destructor does nothing
 */
WaitForHeightM2::~WaitForHeightM2() {

}

/**
 * WP in height measurement
 */
void WaitForHeightM2::inHeightMeasurement() {
#ifdef DEBUG_
	cout << "ERROR --> WP too Small" << endl;
	cout << "WaitForHeightM2::inHeightMeasurement" << endl;
#endif
	new (this) NoDrill();
}

/**
 * WP in tolerance range
 */
void WaitForHeightM2::inToleranceRange() {
#ifdef DEBUG_
	cout << "WaitForHeightM2::inToleranceRange" << endl;
#endif
	new (this) CheckDrillM2();

}

/************************************************************************************
 	 	 	 	 	 	 	 	 NoDrill

 ************************************************************************************/
/**
 * WP has no drill :
 * stop motor and send message to Dispatcher
 */
NoDrill::NoDrill() {
#ifdef DEBUG_
	cout << "ERROR WP Small or Drill Down" << endl;
#endif
	ControllerSegM2::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
}

/**
 * Destructor does nothing
 */
NoDrill::~NoDrill() {

}

/************************************************************************************
 	 	 	 	 	 	 	 	 CheckDrillM2

 ************************************************************************************/
/**
 * WP's Drill is checked
 */
CheckDrillM2::CheckDrillM2() {
#ifdef DEBUG_
	cout << "CheckDrillM2 :: Constructor" << endl;
#endif
}

/**
 * Destructor does nothing
 */
CheckDrillM2::~CheckDrillM2() {

}

/**
 * WP out height measurement
 */
void CheckDrillM2::outHeightMeasurement() {
#ifdef DEBUG_
	cout << "LOCH NACH UNTEN" << endl;
#endif
	new (this) NoDrill();
}

/**
 * WP in tolerance range
 */
void CheckDrillM2::inToleranceRange() {
#ifdef DEBUG_
	cout << "LOCH NACH OBEN" << endl;
#endif

	new (this) DrillOkay();
}

/************************************************************************************
 	 	 	 	 	 	 	 	 DrillOkay

 ************************************************************************************/
/**
 * WP's drill is ok
 */
DrillOkay::DrillOkay() {
#ifdef DEBUG_
	cout << "DrillOkay :: Constructor" << endl;
#endif
}

/**
 * Destructor does nothing
 */
DrillOkay::~DrillOkay() {

}

/**
 * WP is out height measurement after its drill has been checked
 */
void DrillOkay::outHeightMeasurement() {
	new (this) WaitForMetal();
}

/************************************************************************************
 	 	 	 	 	 	 	 	 WaitForMetal

 ************************************************************************************/
/**
 * Constructor does nothing
 */
WaitForMetal::WaitForMetal() {
#ifdef DEBUG_
	cout << "WaitForMetal :: Constructor" << endl;
#endif
}

/**
 * Destructor does nothing
 */
WaitForMetal::~WaitForMetal() {

}

/**
 * WP in switch : stop timer and start new one
 */
void WaitForMetal::inSwitch() {
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->stop();
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->start(THREE_SEC, NULL_MSEC);
	HALAktorik::getInstance()->open_Switch();

	new (this) WorkPieceIsValid();
}

/**
 * WP has metal
 */
void WaitForMetal::isMetal() {
	//HAS Metal
#ifdef DEBUG_
	cout << "WP HAS METAl" << endl;
#endif

	new (this) HasMetall();
}

/************************************************************************************
 	 	 	 	 	 	 	 	 HasMetall

 ************************************************************************************/
/**
 * Constructor does nothing
 */
HasMetall::HasMetall() {
#ifdef DEBUG_
	cout << "HasMetall :: Constructor" << endl;
#endif
}

/**
 * Destructor does nothing
 */
HasMetall::~HasMetall() {

}

/**
 * WP has metal and is in switch :
 * stop timer and start new one for next segment
 */
void HasMetall::inSwitch() {
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->stop();
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->start(FOUR_SEC, NULL_MSEC);

	new (this) WorkPieceIsInvalid();
}

/************************************************************************************
 	 	 	 	 	 	 	 	 WorkPieceIsInvalid

 ************************************************************************************/
/**
 * Constructor does nothing
 */
WorkPieceIsInvalid::WorkPieceIsInvalid() {
#ifdef DEBUG_
	cout << "WorkPieceIsInvalid :: Constructor" << endl;
#endif
}

/**
 * Destructor does nothing
 */
WorkPieceIsInvalid::~WorkPieceIsInvalid() {

}

/**
 * WP is out switch
 */
void WorkPieceIsInvalid::outSwitch() {
	new (this) WaitForLineStart();

}


/************************************************************************************
 	 	 	 	 	 	 	 	 WorkPieceIsValid

 ************************************************************************************/
/**
 * Constructor does nothing
 */
WorkPieceIsValid::WorkPieceIsValid() {
#ifdef DEBUG_
	cout << "WorkPieceIsValid :: Constructor" << endl;
#endif
}

/**
 * Destructor does nothing
 */
WorkPieceIsValid::~WorkPieceIsValid() {

}

/**
 * WP is valid and out switch : close switch
 */
void WorkPieceIsValid::outSwitch() {
	new (this) WaitForEndLine();

	HALAktorik::getInstance()->close_Switch();

}

/************************************************************************************
 	 	 	 	 	 	 	 	 WaitForEndLine

 ************************************************************************************/
/**
 * Constructor does nothing
 */
WaitForEndLine::WaitForEndLine() {
#ifdef DEBUG_
	cout << "WaitForEndLine :: Constructor" << endl;
#endif
}

/**
 * Destructor does nothing
 */
WaitForEndLine::~WaitForEndLine() {

}

/**
 * WP is has left line end : remove WP from fifo and stop motor
 * Notify machine1 that machine2 is ready
 */
void WaitForEndLine::outLineEnd() {
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->stop();
	ControllerSegM2::getInstance()->removeFirsttWP();

	// Wait one second so that workpiece can leave the line
	WAIT_ONE_S;

	HALAktorik::getInstance()->motor_off();
	MainController::getInstance()->setIsRunning(false);
	Sender::getInstance()->send(MACHINE2_IS_READY);

	new (this) WaitForLineStart();
}
