/*
 * WorkPiece.h
 *
 *  Created on: 30.11.2012
 *      Author: aax844
 */

#ifndef WORKPIECE_H_
#define WORKPIECE_H_

class WorkPiece {
public:
	WorkPiece(int id);
	virtual ~WorkPiece();

	bool getIs_inTolleranceRange() const;
	void setIs_inTolleranceRange(bool is_inTolleranceRange_);

    bool getIs_Metal() const;
    void setIs_Metal(bool is_Metal);

    void setHas_Drill(bool has_Drill_);
    bool getHas_Drill() const;

private:
	int wp_id_ ;
	bool is_Metal_;
	bool is_inTolleranceRange_;
	bool has_Drill_;


};

#endif /* WORKPIECE_H_ */
