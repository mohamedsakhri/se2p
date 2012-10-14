#include <cstdlib>
#include <iostream>

#include "MyObject.h"
#include "MyThread.h"
#include<unistd.h>

using namespace std;
using namespace thread;



int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE <SE2P>" << endl;
/*
	MyObject myObject; //konstruktur wird aufgerufen

	myObject.myMethod();
	*/

	MyThread thr;
	thr.start(NULL);
	sleep(10);
	thr.stop();
	thr.join();



	return EXIT_SUCCESS;
}
