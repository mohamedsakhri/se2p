/*
 * Reader.cpp
 *
 *  Created on:
 *      Author: simohamed
 */

#include "Reader.h"
#include "stdint.h"
#include "SerInterface.h"
#include "Constants.h"
#include "Demultiplexer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEBUG_

using namespace std;
Reader::Reader() {
	// TODO Auto-generated constructor stub
}

Reader::~Reader() {
	// TODO Auto-generated destructor stub
}

void Reader::shutdown() {
	close(ser_Interface_id_);
}

void Reader::execute(void *arg) {
#ifdef DEBUG_
	cout << "(reader) thread start" << endl;
#endif
	int fd = open(DEVICE, O_RDWR | O_NOCTTY); // open device with right/right rights
	// this process doesn't want to control the device
	if (fd < 0) {
		perror("Open failed : ");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG_
	cout << "(reader) fd: " << fd << endl;
#endif
	//recieved data will be saved in buffer
	int msg = -1;
	while (!isStopped()) {

#ifdef DEBUG_
		cout << "(reader) waiting for data" << endl;
#endif
		int recieved_size = readcond(fd, &msg, sizeof(msg), 2, 5, 0);
		// did we recieve something ?
		if (recieved_size < 0) {
			perror("Read error : ");
		}
		// did we recieve exactly the size of data we are waiting for ?
		if (recieved_size != sizeof(msg)) {
			cout << "received size != buffer" << endl;
		}
		cout << "###########  ERFOLG: " << msg << endl;

		//TODO put message in pulse messege and send to dispatcher
		Demultiplexer::getInstance()->sendMsg2Dispatcher(msg);
		msg = -1;

	}

}

