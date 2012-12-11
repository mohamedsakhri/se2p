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

	int getId();

	bool getIs_inTolleranceRange();
	void setIs_inTolleranceRange(bool isinTolleranceRange);

    bool getIs_Metal();
    void setIs_Metal(bool isMetal);

    void setHas_Drill(bool hasDrill);
    bool getHas_Drill();

private:
	int wp_id_ ;
	bool is_Metal_;
	bool is_inTolleranceRange_;
	bool has_Drill_;


};

#endif /* WORKPIECE_H_ */
