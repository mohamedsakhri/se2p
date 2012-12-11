/*
 * WorkPiece.cpp
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#include "WorkPiece.h"
#include <iostream.h>

WorkPiece::WorkPiece(int id) {

	wp_id_ = id;
	is_Metal_ = false;
	is_inTolleranceRange_ = false;
	has_Drill_ = false;

}

WorkPiece::~WorkPiece() {

}

int WorkPiece::getId()
{
	return this->wp_id_;
}


void WorkPiece::setIs_inTolleranceRange(bool inTolleranceRange)
{
	this->is_inTolleranceRange_ = inTolleranceRange;
}
bool WorkPiece::getIs_inTolleranceRange()
{
    return this->is_inTolleranceRange_;
}

void WorkPiece::setIs_Metal(bool isMetal)
{
    this->is_Metal_ = isMetal;
}

bool WorkPiece::getIs_Metal()
{
    return this->is_Metal_;
}

void WorkPiece::setHas_Drill(bool hasDrill)
{
    this->has_Drill_ = hasDrill;
}
bool WorkPiece::getHas_Drill()
{
    return this->has_Drill_;
}
