/***************************************************************************
 *
 *    Hochschule fuer Angewandte Wissenschaften Hamburg
 *
 *    WP
 *    Effiziente Datenstrukturen in C++ fuer verteilte Echtzeitprogrammierung
 *
 *	 Prof. Dr. Stephan Pareigis
 *
 *    Thread Class Implementation
 ****************************************************************************/

#include "HAWThread.h"
#include <iostream>

namespace thread {

volatile bool HAWThread::GLOBAL_EXIT = false;

HAWThread::HAWThread() :
	bRunning_(false), LOCAL_EXIT(false) {
}

HAWThread::~HAWThread() {
	cout << "Destructor" << tid_ << endl;
	ThreadDestroy(tid_, 0, 0);

}

void HAWThread::start(void * arg) {
	if (bRunning_){
		cout << "bRunning" << bRunning_ << endl;
		return;
	}
	cout << "bRunning" << bRunning_ << endl;
	bRunning_ = true;
	Arg(arg); // store user data
	int code = pthread_create(&tid_, NULL, (HAWThread::entryPoint), this);
	if (code != 0)
		cout << "Thread could not be started." << endl;
}

void HAWThread::stop() {
	LOCAL_EXIT = true;
}

void HAWThread::hold() {
	ThreadCtl(_NTO_TCTL_ONE_THREAD_HOLD, (void*) tid_);
}
void HAWThread::cont() {
	ThreadCtl(_NTO_TCTL_ONE_THREAD_CONT, (void*) tid_);
}

void HAWThread::run(void * arg) {
	execute(arg);
	shutdown();
}

void* HAWThread::entryPoint(void* pthis) {
	HAWThread* pt = (HAWThread*) pthis;
	pt->run(pt->Arg());
	return NULL;
}

void HAWThread::join() const {
	pthread_join(tid_, NULL );
}
}
;
