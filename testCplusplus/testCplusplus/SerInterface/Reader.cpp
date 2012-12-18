/*
 * @file 	Reader.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 14, 2012
 *
 * This class represents the reader thread, which reads what is sent to the Serial interface.
 */

#include "Reader.h"

//#define DEBUG_

using namespace std;

/**
 * Initialize the communication wit Serial Interface and react in case of fail
 */
Reader::Reader() {
#ifdef DEBUG_
	cout << "Reader :: Constructor " << endl;
#endif
	/*	O_RDWR		: open device with right/right rights
	 * 	O_NOCITY	: this process doesn't want to control the device
	 */
	ser_Interface_id_ = open(DEVICE, O_RDWR | O_NOCTTY);

	if (ser_Interface_id_ < 0) {
		perror("Open failed : ");
		exit(EXIT_FAILURE);
	}
}

/*
 *
 */
void Reader::execute(void *arg) {
#ifdef DEBUG_
	cout << "Reader Thread started" << endl;
#endif

	//received data will be saved in buffer
	int msg = -1;
	while (!isStopped()) {

#ifdef DEBUG_
		cout << "SI : Reader waiting for data " << endl;
#endif
		int recieved_size = readcond(ser_Interface_id_, &msg, sizeof(msg), 2, 5, 0);

		if (recieved_size < 0) {
			perror("Read error : ");
		}
		// did we receive exactly the size of data we are waiting for ?
		if (recieved_size != sizeof(msg)) {
			cout << "Error : Received size != buffer" << endl;
			// Don't send message and go to the next loop
			continue;
		}
#ifdef DEBUG_
		cout << "RECEIVE: " << msg << endl;
#endif
		//Send message to Dispatcher
		Demultiplexer::getInstance()->sendMsg2Dispatcher(msg);

		//Reset message to invalid value to avoid reuse of the last message
		msg = -1;
	}
}

/**
 * Close communication before thread's end
 */
void Reader::shutdown() {
	close(ser_Interface_id_);
}


Reader::~Reader() {
}

