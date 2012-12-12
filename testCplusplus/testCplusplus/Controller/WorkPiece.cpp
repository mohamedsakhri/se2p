/*
 * @file :	WorkPiece.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	30.11.2012
 *
 * This class represents a Workpiece.
 */

#include <iostream.h>
#include "WorkPiece.h"


/**
 * Set workpiece's attribut to default values
 */
WorkPiece::WorkPiece(int id) {
	wp_id_ = id;
	is_Metal_ = false;
	is_inTolleranceRange_ = false;
	has_Drill_ = false;
	tol_counter_ = 0;
}

/**
 * Nothing to do in Destructor!
 */
WorkPiece::~WorkPiece() {

}
/**
 * Return Workpiece Id
 */
int WorkPiece::getId()
{
	return this->wp_id_;
}

/**
 * Set Workpiece's tolerance range status
 */
void WorkPiece::setIs_inTolleranceRange(bool inTolleranceRange)
{
	this->is_inTolleranceRange_ = inTolleranceRange;
}

/**
 * Return Workpiece's tolerance range status
 */
bool WorkPiece::getIs_inTolleranceRange()
{
    return this->is_inTolleranceRange_;
}

/**
 * Set worpiece's metal status
 */
void WorkPiece::setIs_Metal(bool isMetal)
{
    this->is_Metal_ = isMetal;
}

/**
 * Return worpiece's metal status
 */
bool WorkPiece::getIs_Metal()
{
    return this->is_Metal_;
}

/**
 * Set worpiece's drill status
 */
void WorkPiece::setHas_Drill(bool hasDrill)
{
    this->has_Drill_ = hasDrill;
}

/**
 * Return worpiece's drill status
 */
bool WorkPiece::getHas_Drill()
{
    return this->has_Drill_;
}

int WorkPiece::getTolCounter(){
	return tol_counter_;
}

void WorkPiece::incTolCounter(){
	tol_counter_++;
}

void WorkPiece::resetTolCounter(){
	tol_counter_ = 0;
}
