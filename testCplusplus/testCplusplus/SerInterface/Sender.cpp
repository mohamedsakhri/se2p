/*
 * Sender.cpp
 *
 *  Created on : 29.10.2012
 *   *      Author: simohamed
 */

#include "Sender.h"
#include "stdint.h"
#include "SerInterface.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

Sender::Sender() {
	// TODO Auto-generated constructor stub

}

Sender::~Sender() {
	// TODO Auto-generated destructor stub
}

void Sender::execute(void *arg) {

	cout << "sender thread start" << endl;
	ser_Interface_id_ = open(DEVICE, O_RDWR | O_NOCTTY); // open device with right/right rights
	// this process doesn't want to control the device


	if (ser_Interface_id_ < 0) {
		perror("Open failed : ");
		exit(EXIT_FAILURE);
	}
	cout << "fd: " << ser_Interface_id_ << endl;

	char *buffer;
	buffer = "LAB_1";

	while (true) {
		// call write here and react about errors
		int writen_size = write(ser_Interface_id_, buffer, sizeof(buffer));
		usleep(TIME_TO_WAIT);

		//	  cout << "data sent: " << buffer << endl;
		if (writen_size < 0) {
			perror("send error : ");
		}
	}
}

void Sender::shutdown() {
	//	close(ser_Interface_id_);

}
