/*
 * HALintro.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: simohamed
 */
#include "HALAktorik.h"
#include "Adresse.h"


	HALintro* instance = new HALintro();
using namespace std;

HALintro::HALintro()
{
	//instance = NULL;
	out8(DIO_BASE, 0x8A);
	out8(DIO_BASE+DIO_OFFS_A, 0x00);
	out8(DIO_BASE+DIO_OFFS_C, 0x00);

}

HALintro::~HALintro()
{
	// TODO Auto-generated destructor stub
	delete instance;
	instance = NULL;

}
HALintro *HALintro::getInstance()
{
	if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
		perror("ThreadCtl access failed\n");
		return NULL;
	}

	if (instance == NULL) {
		instance = new HALintro();
	}
	return instance;

}

void HALintro::lampeRotAn()
{
	uint8_t val = in8(DIO_BASE + DIO_OFFS_A);
	out8(DIO_BASE + DIO_OFFS_A, val | BIT_7);
}
