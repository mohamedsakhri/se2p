/*
 * MyThread.cpp
 *
 *  Created on: 11.10.2012
 *      Author: aar740
 */

#include "MyThread.h"
#include<unistd.h>

namespace thread {

MyThread::MyThread() {
	// TODO Auto-generated constructor stub

}

MyThread::~MyThread() {
	// TODO Auto-generated destructor stub
}

    void MyThread::shutdown()
    {
    	cout << "shuting down.. " << endl;
    }

    void MyThread::execute(void *arg)
    {
    	while(!isStopped())
    	{
    		cout << "er ist ein thread" << endl;
    		usleep(50000);
    	}
    }

}
