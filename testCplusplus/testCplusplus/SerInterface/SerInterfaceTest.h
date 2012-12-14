/*
 * SerInterfaceTest.h
 *
 *  Created on: 30.10.2012
 *      Author: aax877
 */

#ifndef SERINTERFACETEST_H_
#define SERINTERFACETEST_H_

#include "SerInterface.h"
#include "Sender.h"
#include "Reader.h"
#include "Constants.h"

class SerInterfaceTest {
public:
	SerInterfaceTest();
	virtual ~SerInterfaceTest();
private:
	SerInterface *SRtest;
};

#endif /* SERINTERFACETEST_H_ */
