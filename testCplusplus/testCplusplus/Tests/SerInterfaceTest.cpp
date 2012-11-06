/*
 * SerInterfaceTest.cpp
 *
 *  Created on: 30.10.2012
 *      Author: aax877
 */

#include "SerInterfaceTest.h"
//#include "SerInterface.h"


SerInterfaceTest::SerInterfaceTest() {
	// TODO Auto-generated constructor stub
	Reader rdr;
	rdr.start(NULL);

	Sender sdr;
	sdr.start(NULL);

	sdr.join();
	rdr.join();
}

SerInterfaceTest::~SerInterfaceTest() {
	// TODO Auto-generated destructor stub
	cout << "Serial interface test end" << endl;
	delete SRtest;
}
