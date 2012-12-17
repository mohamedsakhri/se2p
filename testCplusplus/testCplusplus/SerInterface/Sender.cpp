/*
 * @file 	Sender.cpp
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 *
 * @date	 Dec 14, 2012
 *
 * This class represents the sender. It initialize the Serial Interface
 * and offers a method to send messages.
 *
 */
#include "Sender.h"

#define DEBUG_

using namespace std;

Mutex Sender::sender_mutex_ = Mutex();
Sender* Sender::sender_instance_ = NULL ;

/**
 * Initialize the communication wit Serial Interface and react in case of fail
 */
Sender::Sender() {
#ifdef DEBUG_
	cout << "Sender :: Constructor " << endl;
#endif

	/*	O_RDWR		: open device with right/right rights
	 * 	O_NOCITY	: this process doesn't want to control the device
	 */
	ser_Interface_id_ = open(DEVICE, O_RDWR | O_NOCTTY);

	if (ser_Interface_id_ < 0) {
		perror("Open failed : ");
		exit( EXIT_FAILURE);
	}
}

/**
 * Return the only instance of Sender, which is implemented as Singleton pattern.
 */
Sender* Sender::getInstance() {

	if (!sender_instance_) {
		sender_mutex_.lock();
		if (!sender_instance_) {
			sender_instance_ = new Sender;
		}
		sender_mutex_.unlock();
	}
	return sender_instance_;
}

/**
 * Send message to the serial interface and test if the operation has been successful
 */
void Sender::send(int message) {
#ifdef DEBUG_
	cout << "Sender :: send " << endl;
#endif

	int writen_size = write(ser_Interface_id_, &message, sizeof(message));
	//TODO do we need to wait!
	usleep( TIME_TO_WAIT);

	if (writen_size < 0) {
		perror("send error : ");
	}
}

/**
 * Close the communication with the Serial Interface
 */
Sender::~Sender() {
	close(ser_Interface_id_);
}
