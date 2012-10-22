/*
 * HALintro.h
 *
 *  Created on: Oct 18, 2012
 *      Author: simohamed
 */
#ifndef HALINTRO_H_
#define HALINTRO_H_
#include "HWaccess.h"
#include "Adresse.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <errno.h>
class HALintro {
public:
	HALintro();
	virtual ~HALintro();

private :
	HALintro* getInstance();
	// Aktoren PORT A
  	void lampeRotAn();
  	void lampeRotAus();
  	void lampeGruenAn();
  	void lampeGruenAus();
  	void lampeGelbAn();
  	void lampeGelbAus();
  	void scheibeAuf();
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

#endif /* HALINTRO_H_ */
