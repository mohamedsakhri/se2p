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
#define INTERRUPT_CTR_REG (D_IOBASE + 0x0B)			//!< Interrupt control (Enable Chg-of-St. Interrupt)
#define PB_CTR 0x02
#define PC_LOW_CTR 0x04
#define READ_IRQ_CLEAR_INTERRUPT (D_IOBASE + 0x18)	//!< Read IRQ register and clear Interrupt register
													//!< in the same time. See DIO p.18
#define IRQ 11										//!< IRQ
#define IIR_PORTB 0x02
#define IIR_PORTC 0x08

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

/*
 *  AIO Card Base and Ports Addresses
 *
 */
#define A_IOBASE 0x320  				// TO BE REPLACED WITH THE RIGHT ADDRESS. See AIO Manual p.14
#define AIO_CONVERT_CONTROL 0x10  		// See AIO Manual p. 18
#define AD_C_LOW_OFFS 0x02  			// AIO p. 16

/**
 * Port B and Port C high bits' meaning
 */

#define START_BUTTON 0x01
#define STOP_BUTTON 0x02
#define RESET_BUTTON 0x04
#define E_STOP_BUTTON 0x08
#define LIGHT_BARRIER_1 0x10
#define HEIGHT_SENSOR 0x20
#define HEIGHT_STATUS 0x40
#define WP_IN_SWITCH 0x80
#define METAL_STATUS 0x100
#define SWITCH_STATUS 0x200
#define SLIDE_STATUS 0x400
#define LIGHT_BARRIER_2 0x800

#endif /* ADDRESS_H_ */

