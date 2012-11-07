/*
 * Address.h
 *
 *  Created on: Oct 21, 2012
 *      Author: aksil
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

/*
 *  Digital Card Base and Ports Adresses
 *
 */
#define D_IOBASE 0x300 								//!< Base adress
#define DIGITAL_CARD_CONTROL (D_IOBASE + 0x03) 		//!< Control adress
#define DIGITAL_CARD_CROUP0_PORTA (D_IOBASE + 0x00) //!< Port A adress
#define DIGITAL_CARD_CROUP0_PORTB (D_IOBASE + 0x01) //!< Port B adress
#define DIGITAL_CARD_CROUP0_PORTC (D_IOBASE + 0x02) //!< Port C adress

#define INTERRUPT_STATUS_REG (D_IOBASE + 0x0F)		//!< Status register

/*
 * Using BIT_x instead of some magic numbers
 *
 */
#define BIT_0 0x01
#define BIT_1 0x02
#define BIT_2 0x04
#define BIT_3 0x08
#define BIT_4 0x10
#define BIT_5 0x20
#define BIT_6 0x40
#define BIT_7 0x80

#endif /* ADDRESS_H_ */

