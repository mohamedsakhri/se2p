/*
 * Address.h
 *
 *  Created on: Oct 21, 2012
 *      Author: aksil
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_


#define D_IOBASE 0x300 								// Anfangsadresse Ports
#define DIGITAL_CARD_CONTROL (D_IOBASE + 0x03) 		// Adresse von Card Control
#define DIGITAL_CARD_CROUP0_PORTA (D_IOBASE + 0x00) // Adresse von Port A
#define DIGITAL_CARD_CROUP0_PORTB (D_IOBASE + 0x01) // Adresse von Port B
#define DIGITAL_CARD_CROUP0_PORTC (D_IOBASE + 0x02) // Adresse von Port C


#define BIT_0 0x01
#define BIT_1 0x02
#define BIT_2 0x04
#define BIT_3 0x08
#define BIT_4 0x10
#define BIT_5 0x20
#define BIT_6 0x40
#define BIT_7 0x80



#endif /* ADDRESS_H_ */




