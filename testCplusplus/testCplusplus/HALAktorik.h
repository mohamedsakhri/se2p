/*
 * HALAktorik.h
 *
 *  Created on: Oct 18, 2012
 *      Author: simohamed
 */

#include "HWaccess.h"
#include "Adress.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <errno.h>

#ifndef HALAktorik_H_
#define HALAktorik_H_

class HALAktorik {
public:
	//constructor
	HALAktorik();
	//destructor
	virtual ~HALAktorik();


	HALAktorik* getInstance();
	// Aktoren PORT A
  	static void lampeRotAn();
  	static void lampeRotAus();
  	static void lampeGruenAn();
  	static void lampeGruenAus();
  	static void lampeGelbAn();
  	static void lampeGelbAus();
  	static void scheibeAuf();
  	void motorAn();
  	void motorAus();
  	void motorLangsamLaufen();
  	void bandRechtsLaufen();
  	void bandLinksLaufen();
  	//Akotren Port C
  	void startLEDLeuchten();
  	void startLEDDunkel();
  	void Q1LEDDeuchten();
  	void Q1LEDDunkel();
  	void Q2LEDLeuchten();
  	void Q2LEDDunkel();

};


#endif /* HALAktorik_H_ */
