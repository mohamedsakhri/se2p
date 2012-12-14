/*
 * Sender.h
 *
 *  Created on
 *      Author: simohamed
 */

#ifndef SENDER_H_
#define SENDER_H_





class Sender{
public:
	Sender();
	virtual ~Sender();
	virtual void send(int message);
//	virtual void shutdown();
private:
	int ser_Interface_id_;
};

#endif /* SENDER_H_ */
