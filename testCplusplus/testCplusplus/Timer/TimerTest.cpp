/*
 * @file	TimerTest.cpp
 *
 * @author	Martin Hepke
 *
 * @date	 Dec 14, 2012
 *
 * This class is used to test the Software's timer
 */

#include "TimerTest.h"
#include "Timer.h"
#include <iostream>

TimerTest::TimerTest() {

}

TimerTest::~TimerTest() {
}

void TimerTest::execute(void *arg) {
	struct _pulse msg;
	int tchid = ChannelCreate(0);
	Timer *ourTestTimer = new Timer(5, 0, tchid, MY_PULSE_COD2, WP_IS_MISSING);
	Timer *ourTestTimer2 = new Timer(12, 50000000, tchid, MY_PULSE_CODE,
			WP_IS_MISSING);
	int trcvid;
	cout << "Channel ID(TimerTest)" << (int) tchid << endl;
	ConnectAttach(0, 0, tchid, _NTO_SIDE_CHANNEL, 0);
	ourTestTimer->start();
	ourTestTimer2->start();
	cout << "Start the Timer" << endl;

	for (;;) {
		cout << "Waiting for Message to be received" << endl;
		trcvid = MsgReceivePulse(tchid, &msg, sizeof(msg), NULL);
		if (trcvid == 0) { /* we got a pulse */
			if (msg.code == MY_PULSE_COD2) {
				/*
				 cout << "Remaining Time on Timer 1:" << ourTestTimer->getRemainingTime() << endl;

				 */
				cout << "Got Pulse from Timer 1" << endl;
				ourTestTimer2->start();
			} else {
				if (msg.code == MY_PULSE_CODE)
					cout << "Got Pulse from Timer 2" << endl;
			}
		}
	}
	cout << "Got NO Pulse" << endl;
}

void TimerTest::shutdown() {
}
