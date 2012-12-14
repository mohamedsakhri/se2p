/*
 * @file	SegHeight.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 10, 2012
 *
 * Classes which represent all states in Segment 2
 *
 */

#include "SegHeight.h"
#define DEBUG_

/************************************************************************************
 *									WaitingHeighM1									*
 *																					*
 ************************************************************************************/

WaitingHeightM1::WaitingHeightM1(){
#ifdef DEBUG_
	cout << "WaitingHeightM1 :: Constructor" << endl;
#endif
}

WaitingHeightM1::~WaitingHeightM1() {

}

void WaitingHeightM1::inHeightMeasurement(){
#ifdef DEBUG_
	cout << "WaitingHeightM1 :: inHeightMeasurement" << endl;
#endif

	new (this) TooSmall();
}

void WaitingHeightM1::inToleranceRange(){
#ifdef DEBUG_
	cout << "WaitingHeightM1 :: inToleranceRange" << endl;
#endif
	//TODO WP's Id !!
	(ControllerSeg2::getInstance()->getFirstWP())->setIs_inTolleranceRange(true);
		ControllerSeg2::getInstance()->getFirstWP()->setHas_Drill(false);

	new (this) CheckDrill();
}


/************************************************************************************
 *									TooSmall										*
 *																					*
 ************************************************************************************/

TooSmall::TooSmall(){
	cout << "TooSmall :: Constructor" << endl;
}

TooSmall::~TooSmall(){

}

void TooSmall::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "TooSmall :: outHeightMeasurement" << endl;
#endif
	// Start timer ??
	if (!ControllerSeg2::getInstance()->isFifoEmpty()) {
		ControllerSeg2::getInstance()->passWP2Ctr();
		ControllerSeg2::getInstance()->removeFirsttWP();

		new (this) WaitingHeightM1();
	} else {
		//TODO  just send msg and let controller do the rest according to the error event handler
		ControllerSeg2::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
		HALAktorik::getInstance()->motor_off();
		HALAktorik::getInstance()->red_Light_on();
		HALAktorik::getInstance()->green_Light_off();
	}
}


/************************************************************************************
 *									CheckDrill										*
 *																					*
 ************************************************************************************/

CheckDrill::CheckDrill(){
	cout << "CheckDrill :: Constructor" << endl;
}

CheckDrill::~CheckDrill(){

}

void CheckDrill::outHeightMeasurement(){
#ifdef DEBUG_
	cout << "CheckDrill :: inHeightMeasurement" << endl;
#endif

//		ControllerSeg2::getInstance()->getFirstWP()->setHas_Drill(true);
			if (!ControllerSeg2::getInstance()->isFifoEmpty()) {
#ifdef DEBUG_
				if(ControllerSeg2::getInstance()->getFirstWP()->getHas_Drill()){
					cout << "----------> LOCH : OBEN" << endl;
				}else {
					cout << "----------> LOCH : UNTEN" << endl;

				}
#endif
				ControllerSeg2::getInstance()->passWP2Ctr();
				ControllerSeg2::getInstance()->removeFirsttWP();

				new (this) WaitingHeightM1();
			} else {
				//TODO  just send msg and let controller do the rest according to the error event handler
				ControllerSeg2::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
				HALAktorik::getInstance()->motor_off();
				HALAktorik::getInstance()->red_Light_on();
				HALAktorik::getInstance()->green_Light_off();
			}
	new (this) WaitingHeightM1();
}


void CheckDrill::inToleranceRange(){
#ifdef DEBUG_
	cout << "CheckDrill :: notInToleranceRange " << endl;
#endif

	ControllerSeg2::getInstance()->getFirstWP()->setHas_Drill(true);
}






// TODO to be removed if we are 100% we don't need it anymore


/************************************************************************************
 *									DrillChecked									*
 *																					*
 ************************************************************************************/
//
//DrillChecked::DrillChecked(){
//	cout << "DrillChecked constructor" << endl;
//}
//
//DrillChecked::~DrillChecked(){
//
//}
//
//void DrillChecked::outHeightMeasurement(){
//#ifdef DEBUG_
//	cout << "DrillChecked::outHeightMeasurement" << endl;
//#endif
//
//	if(ControllerSeg2::getInstance()->getFirstWP()->getHas_Drill()){
//		cout << "WP has LOCH nach OBEN" << endl;
//	}else {
//		cout << "WP has LOCH nach UNTEN" << endl;
//
//	}
//	// Start timer ??
//	if (!ControllerSeg2::getInstance()->isFifoEmpty()) {
//		ControllerSeg2::getInstance()->passWP2Ctr();
//		ControllerSeg2::getInstance()->removeFirsttWP();
//
//		new (this) WaitingHeightM1();
//	} else {
// just send msg and let controller do the rest according to the error event handler
//		ControllerSeg2::getInstance()->sendMsg2Dispatcher(WP_IS_STRANGER);
//		HALAktorik::getInstance()->motor_off();
//		HALAktorik::getInstance()->red_Light_on();
//		HALAktorik::getInstance()->green_Light_off();
//	}
//}

