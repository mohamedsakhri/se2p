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
 * Deconstructor has nothing to do
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
 *
 */
WpIsComming::WpIsComming() {
#ifdef DEBUG_
	cout << "WpIsComming :: Constructor" << endl;
#endif
}

/**
 *
 */
WpIsComming::~WpIsComming() {
}

/**
 *
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
 *
 */
WaitForHeightM2::WaitForHeightM2() {
#ifdef DEBUG_
	cout << "WaitForHeightM2 :: Constructor" << endl;
#endif
}

/**
 *
 */
WaitForHeightM2::~WaitForHeightM2() {

}

/**
 *
 */
void WaitForHeightM2::inHeightMeasurement() {
#ifdef DEBUG_
	cout << "ERROR --> WP too Small" << endl;
	cout << "WaitForHeightM2::inHeightMeasurement" << endl;
#endif
	new (this) NoDrill();
}

/**
 *
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
//TODO error (if drill down or small WP)
/**
 *
 */
NoDrill::NoDrill() {
	cout << "ERROR WP Small or Drill Down" << endl;
//	HALAktorik::getInstance()->red_Light_on();
//	HALAktorik::getInstance()->green_Light_off();
	HALAktorik::getInstance()->motor_off();
}

NoDrill::~NoDrill() {

}

/************************************************************************************
 	 	 	 	 	 	 	 	 CheckDrillM2

 ************************************************************************************/
/**
 *
 */
CheckDrillM2::CheckDrillM2() {
#ifdef DEBUG_
	cout << "CheckDrillM2 :: Constructor" << endl;
#endif
}

/**
 *
 */
CheckDrillM2::~CheckDrillM2() {

}

/**
 *
 */
void CheckDrillM2::outHeightMeasurement() {
#ifdef DEBUG_
	cout << "LOCH NACH UNTEN" << endl;
#endif
	new (this) NoDrill();
}

/**
 *
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
 *
 */
DrillOkay::DrillOkay() {
#ifdef DEBUG_
	cout << "DrillOkay :: Constructor" << endl;
#endif
}

/**
 *
 */
DrillOkay::~DrillOkay() {

}

/**
 *
 */
void DrillOkay::outHeightMeasurement() {
	new (this) WaitForMetal();
}

/************************************************************************************
 	 	 	 	 	 	 	 	 WaitForMetal

 ************************************************************************************/
/**
 *
 */
WaitForMetal::WaitForMetal() {
#ifdef DEBUG_
	cout << "WaitForMetal :: Constructor" << endl;
#endif
}

/**
 *
 */
WaitForMetal::~WaitForMetal() {

}

/**
 *
 */
void WaitForMetal::inSwitch() {
	//No Metall
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->stop();
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->start(THREE_SEC, NULL_MSEC);
	HALAktorik::getInstance()->open_Switch();

	new (this) WorkPieceIsValid();
}

/**
 *
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
HasMetall::HasMetall() {
#ifdef DEBUG_
	cout << "HasMetall :: Constructor" << endl;
#endif
}

/**
 *
 */
HasMetall::~HasMetall() {

}

/**
 *
 */
void HasMetall::inSwitch() {
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->stop();
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->setNewTime(4, 0);
	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->start(FOUR_SEC, NULL_MSEC);
	new (this) WorkPieceIsInvalid();
}

/************************************************************************************
 	 	 	 	 	 	 	 	 WorkPieceIsInvalid

 ************************************************************************************/
/**
 *
 */
WorkPieceIsInvalid::WorkPieceIsInvalid() {
#ifdef DEBUG_
	cout << "WorkPieceIsInvalid :: Constructor" << endl;
#endif
}

/**
 *
 */
WorkPieceIsInvalid::~WorkPieceIsInvalid() {

}

/**
 *
 */
void WorkPieceIsInvalid::outSwitch() {
	new (this) WaitForLineStart();

//	new (this) InSlideM2();
}

///************************************************************************************
// 	 	 	 	 	 	 	 	 InSlideM2
//
// ************************************************************************************/
///**
// *
// */
//InSlideM2::InSlideM2() {
//#ifdef DEBUG_
//	cout << "InSlideM2 :: Constructor" << endl;
//#endif
//}
//
///**
// *
// */
//InSlideM2::~InSlideM2() {
//
//}
//
///**
// * Workpiece has left slide :
// * Remove it from fifo
// * Notify machine 1 that machine 2 is ready
// * Stop motor
// */
//void InSlideM2::outSlide() {
//	ControllerSegM2::getInstance()->getFirstWP()->getTimer()->stop();
//	ControllerSegM2::getInstance()->removeFirsttWP();
//	Sender::getInstance()->send(MACHINE2_IS_READY);
//	HALAktorik::getInstance()->motor_off();
//
//
//	new (this) WaitForLineStart();
//
//}

/************************************************************************************
 	 	 	 	 	 	 	 	 WorkPieceIsValid

 ************************************************************************************/
/**
 *
 */
WorkPieceIsValid::WorkPieceIsValid() {
#ifdef DEBUG_
	cout << "WorkPieceIsValid :: Constructor" << endl;
#endif
}

/**
 *
 */
WorkPieceIsValid::~WorkPieceIsValid() {

}

/**
 *
 */
void WorkPieceIsValid::outSwitch() {
	new (this) WaitForEndLine();
	HALAktorik::getInstance()->close_Switch();

}

/************************************************************************************
 	 	 	 	 	 	 	 	 WaitForEndLine

 ************************************************************************************/
/**
 *
 */
WaitForEndLine::WaitForEndLine() {
#ifdef DEBUG_
	cout << "WaitForEndLine :: Constructor" << endl;
#endif
}

/**
 *
 */
WaitForEndLine::~WaitForEndLine() {

}

/**
 *
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
