/*
 * HALAktorik.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: simohamed
 */

#include "HALAktorik.h"
#include "Adress.h"

HALAktorik* instance = new HALAktorik();

using namespace std;

HALAktorik::HALAktorik()
{
	instance = NULL;


	out8(DIGITAL_CARD_CONTROL, 0x8A);
	out8(DIGITAL_CARD_CROUP0_PORTA, 0x00);
	out8(DIGITAL_CARD_CROUP0_PORTC, 0x00);

}

HALAktorik::~HALAktorik()
{
	// TODO Auto-generated destructor stub
	delete instance;
	instance = NULL;

}
HALAktorik *HALAktorik::getInstance()
{
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
		return NULL;
	}

	if (instance == NULL) {
		instance = new HALAktorik();
	}
	return instance;

}

void HALAktorik::lampeRotAn()
{
	uint8_t val = in8(DIGITAL_CARD_CROUP0_PORTA);
	//cout << val << endl;
	//out8(DIGITAL_CARD_CROUP0_PORTA, val | BIT_7);
	out8(DIGITAL_CARD_CROUP0_PORTA, 0x80 | val);
}

void HALAktorik::lampeRotAus()
{
	 uint8_t val = in8(DIGITAL_CARD_CROUP0_PORTA);
	 out8(DIGITAL_CARD_CROUP0_PORTA, 0x80 ^ val);
}

 void HALAktorik::lampeGruenAn()
 {
	 uint8_t val = in8(DIGITAL_CARD_CROUP0_PORTA);
	 out8(DIGITAL_CARD_CROUP0_PORTA, 0x20 | val);
 }

 void HALAktorik::lampeGruenAus()
  {
 	 uint8_t val = in8(DIGITAL_CARD_CROUP0_PORTA);
 	 out8(DIGITAL_CARD_CROUP0_PORTA, 0x20 ^ val);
  }

 void HALAktorik::lampeGelbAn()
 {
 	uint8_t val = in8(DIGITAL_CARD_CROUP0_PORTA);
 	cout << val << endl;
 	//out8(DIGITAL_CARD_CROUP0_PORTA, val | BIT_7);
 	out8(DIGITAL_CARD_CROUP0_PORTA, 0x40);
 }

 void HALAktorik::lampeGelbAus()
 {
 	 uint8_t val = in8(DIGITAL_CARD_CROUP0_PORTA);
 	 out8(DIGITAL_CARD_CROUP0_PORTA, 0x40 ^ val);
 }

 void HALAktorik::scheibeAuf()
  {
  	 uint8_t val = in8(DIGITAL_CARD_CROUP0_PORTA);
  	 out8(DIGITAL_CARD_CROUP0_PORTA, 0x10 | val);
  }
