/*
 * StateMachine2.cpp
 *
 *  Created on: 14.12.2012
 *      Author: aax844
 */

#include "SegMachine2.h"
#define DEBUG_


//************************* WaitForLinestart ***************************
WaitForLineStart::WaitForLineStart()
{
#ifdef DEBUG_
	cout << "WaitForLineStart :: Constructor" << endl;
#endif
}

WaitForLineStart::~WaitForLineStart()
{

}

void WaitForLineStart::wpIsComming()
{
	HALAktorik::getInstance()->motor_on();
	//send msg with busy message schon implementiert in controller
	new (this) WpIsComming();
}


//************************* WpIsComming ***************************
WpIsComming::WpIsComming()
{
#ifdef DEBUG_
	cout << "WpIsComming :: Constructor" << endl;
#endif
}

WpIsComming::~WpIsComming()
{
}

void WpIsComming::inLineStart()
{

	new (this) WaitForHeightM2();
}


//************************* WaitForHeightM2 ***************************

WaitForHeightM2::WaitForHeightM2()
{
#ifdef DEBUG_
	cout << "WaitForHeightM2 :: Constructor" << endl;
#endif
}

WaitForHeightM2::~WaitForHeightM2()
{

}

void WaitForHeightM2::inHeightMeasurement()
{
	cout << "WaitForHeightM2::inHeightMeasurement" << endl;
	new (this) NoDrill();
}

void WaitForHeightM2::inToleranceRange()
{
	cout << "WaitForHeightM2::inTolerance" << endl;
	new (this) CheckDrillM2();

}


//************************* noDrill ***************************
//TODO error (if drill down or small WP)
NoDrill::NoDrill()
{
	cout << "ERROR WP Small or Drill Down" << endl;
	HALAktorik::getInstance()->red_Light_on();
	HALAktorik::getInstance()->green_Light_off();
	HALAktorik::getInstance()->motor_off();
}

NoDrill::~NoDrill()
{

}


//************************* CheckDrillM2 ***************************

CheckDrillM2::CheckDrillM2()
{
#ifdef DEBUG_
	cout << "CheckDrillM2 :: Constructor" << endl;
#endif
}
CheckDrillM2::~CheckDrillM2()
{

}

void CheckDrillM2::outHeightMeasurement()
{
	new (this) NoDrill();
}
void CheckDrillM2::inToleranceRange()
{
	//Drill is UP
	new (this) DrillOkay();
}

//************************* DrillOkay ***************************

DrillOkay::DrillOkay()
{
#ifdef DEBUG_
	cout << "DrillOkay :: Constructor" << endl;
#endif
}
DrillOkay::~DrillOkay()
{

}

void DrillOkay::outHeightMeasurement()
{
	new (this) WaitForMetal();
}

//************************* WaitForMetal ***************************

WaitForMetal::WaitForMetal()
{
#ifdef DEBUG_
	cout << "WaitForMetal :: Constructor" << endl;
#endif
}
WaitForMetal::~WaitForMetal()
{

}

void WaitForMetal::inSwitch()
{
	//No Metall
	HALAktorik::getInstance()->open_Switch();
	new (this) WorkPieceIsValid();
}
void WaitForMetal::isMetal()
{
	//HAS Metal
	new (this) HasMetall();
}


//************************* HasMetal ***************************
HasMetall::HasMetall()
{
#ifdef DEBUG_
	cout << "HasMetall :: Constructor" << endl;
#endif
}
HasMetall::~HasMetall()
{

}

void HasMetall::inSwitch()
{
	new (this) WorkPieceIsInvalid();
}


//************************* WorkPieceIsInvalid ***************************
WorkPieceIsInvalid::WorkPieceIsInvalid()
{
#ifdef DEBUG_
	cout << "WorkPieceIsInvalid :: Constructor" << endl;
#endif
}
WorkPieceIsInvalid::~WorkPieceIsInvalid()
{

}

void WorkPieceIsInvalid::outSwitch()
{

	new (this) InSlideM2();
}


//************************* InSlideM2 ***************************
InSlideM2::InSlideM2()
{
#ifdef DEBUG_
	cout << "InSlideM2 :: Constructor" << endl;
#endif
}

InSlideM2::~InSlideM2()
{

}

void InSlideM2::outSlide()
{
	HALAktorik::getInstance()->motor_off();
	//Send msg with ready
	new (this) WaitForLineStart();

}

//************************* WorkPieceIsValid ***********************
WorkPieceIsValid::WorkPieceIsValid()
{
#ifdef DEBUG_
	cout << "WorkPieceIsValid :: Constructor" << endl;
#endif
}

WorkPieceIsValid::~WorkPieceIsValid()
{

}

void WorkPieceIsValid::outSwitch()
{

	new (this) WaitForEndLine();
	WAIT_HALF_S;
	HALAktorik::getInstance()->close_Switch();

}

//************************* WaitForEndLine ***********************
WaitForEndLine::WaitForEndLine()
{
#ifdef DEBUG_
	cout << "WaitForEndLine :: Constructor" << endl;
#endif
}

WaitForEndLine::~WaitForEndLine()
{

}

void WaitForEndLine::outLineEnd()
{
	WAIT_ONE_S;
	HALAktorik::getInstance()->motor_off();
	//sen msg with ready
	new (this) WaitForLineStart();


}
