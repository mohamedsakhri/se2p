/*
 * MyThread.cpp
 *
 *  Created on: 11.10.2012
 *      Author: aar740
 */

// Die Header Datei HWaccess.h steuert den Zugriff auf die HW bzw. Simulation
// Sie muss in jeder Datei stehen, die auf die HW zugreift


#include<unistd.h>
#include <cstdlib>
#include <iostream>
#include <errno.h>
#include "MyThread.h"
#include "HALAktorik.h"





namespace thread {

MyThread::MyThread() {
	// TODO Auto-generated constructor stub

}

MyThread::~MyThread() {
	// TODO Auto-generated destructor stub
}

    void MyThread::shutdown()
    {
    	cout << "Test beendet" << endl;
    }

    void MyThread::execute(void *arg)
    {
    	while(!isStopped())
    	{

    		HALAktorik::lampeRotAn();
    		cout << "RED" << endl;
    	  	sleep(1);
    	  	HALAktorik::lampeGruenAn();
    	  	cout << "RED and Green" << endl;
    	  	sleep(1);
    	}

    		/*
    		// Simpler Test des HW Zugriffs ohne Klassen, Pattern etc.
    			// Reicht nicht fuer den ersten Meilenstein aus

    			// Zugriffsrechte fuer den Zugriff auf die HW holen
    			if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
    				perror("ThreadCtl access failed\n");
    				return;
    			}
    			// Initialisierung der Digitalen IO Karte
    			out8(DIGITAL_CARD_CONTROL, 0x82);

    			// Treibe die Ampel
    			for (int count = 0; count < 20; count ++) {
    				cout << "rot" << endl;
    				out8(D_IOBASE, 0x80);//rot
    				sleep(1);

    				cout << "gelb" << endl;
    				out8(D_IOBASE, 0x40);//gelb
    				sleep(1);

    				cout << "gruen" << endl;
    				out8(D_IOBASE, 0x20);//gruen
    				sleep(1);
    			}
    	}*/


    }

}
