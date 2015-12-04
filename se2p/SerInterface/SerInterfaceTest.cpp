/*
 * SerInterfaceTest.cpp
 *
 *  Created on: 30.10.2012
 *      Author: aax877
 */

#include "SerInterfaceTest.h"
#include "Messages.h"
//#include "SerInterface.h"


SerInterfaceTest::SerInterfaceTest() {
	// TODO Auto-generated constructor stub
	cout << "Serial interface test start" << endl;
	Reader rdr;
	rdr.start(NULL);

	Sender::getInstance()->send(WP_IN_ENGINE_END);
	Sender::getInstance()->send(WP_IN_ENGINE_START);


	rdr.join();
}

SerInterfaceTest::~SerInterfaceTest() {
	// TODO Auto-generated destructor stub
	cout << "Serial interface test end" << endl;
}
