/*
 * MyObject.cpp
 *
 *  Created on: 11.10.2012
 *      Author: aar740
 */

#include "MyObject.h"
#include "iostream"  //cout

using namespace std;


MyObject::MyObject() {
		cout << "constroctur Auruf" <<endl;
}

MyObject::~MyObject() {
		cout << "destroctur Auruf" <<endl;
}

void MyObject::myMethod(){

		cout<< "Hallo" <<endl;
}


