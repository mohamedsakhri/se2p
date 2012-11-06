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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
	cout << "(reader) thread start" << endl;
	int fd = open(DEVICE, O_RDWR | O_NOCTTY); // open device with right/right rights
	// this process doesn't want to control the device
	if (fd < 0) {
		perror("Open failed : ");
		exit(EXIT_FAILURE);
	}

	cout << "(reader) fd: " << fd << endl;

	//recieved data will be saved in buffer
	char buffer[DATA_SIZE];

	while (true) {
		//  usleep(TIME_TO_WAIT);
		cout << "(reader) waiting for data" << endl;
		int recieved_size = readcond(fd, buffer, sizeof(buffer), 2, 5, 0);

		cout << "(reader) recieved_size: " << recieved_size << endl;

		// did we recieve something ?
		if (recieved_size < 0) {
			perror("Read error : ");
		}

		// did we recieve exactly the size of data we are waiting for ?
		if (recieved_size != sizeof(buffer)) {
			cout << "received size != buffer" << endl;
		}

		cout << "###########  ERFOLG: " << buffer << endl;

	}

}

