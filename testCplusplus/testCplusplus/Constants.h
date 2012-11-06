/*
 * Constants.h
 *
 *  Created on: 31.10.2012
 *      Author: aax877
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include <unistd.h>


#define WAIT_ONE_S sleep(1)
#define WAIT_THREE_S sleep(3)
#define WAIT_FIVE_S sleep(5)
#define WAIT_TEN_S sleep(10)

#define WAIT_HALF_S usleep(500000);

#define DATA_SIZE 8    //serial interface send


#endif /* CONSTANTS_H_ */
