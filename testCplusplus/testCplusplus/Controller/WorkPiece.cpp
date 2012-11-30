/*
 * WorkPiece.cpp
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#include "WorkPiece.h"

WorkPiece::WorkPiece(int id) {

	wp_id_ = id;
	is_Metal_ = false;
	is_inTolleranceRange_ = false;
	has_Drill_ = false;

}

WorkPiece::~WorkPiece() {

}


void WorkPiece::setIs_inTolleranceRange(bool is_inTolleranceRange_)
{
    this->is_inTolleranceRange_ = is_inTolleranceRange_;
}
bool WorkPiece::getIs_inTolleranceRange() const
{
    return is_inTolleranceRange_;
}

void WorkPiece::setIs_Metal(bool is_Metal_)
{
    this->is_Metal_ = is_Metal_;
}

bool WorkPiece::getIs_Metal() const
{
    return is_Metal_;
}

void WorkPiece::setHas_Drill(bool has_Drill_)
{
    this->has_Drill_ = has_Drill_;
}
bool WorkPiece::getHas_Drill() const
{
    return has_Drill_;
}
