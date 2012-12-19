/*
 * Constants.h
 *
 *  Created on: 31.10.2012
 *      Author: aax877
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include <unistd.h>

//sleep code
#define WAIT_ONE_S sleep(1)
#define WAIT_THREE_S sleep(3)
#define WAIT_FIVE_S sleep(5)
#define WAIT_TEN_S sleep(10)

#define WAIT_HALF_S usleep(500000);

#define DATA_SIZE 8    //serial interface send

// Controllers Ids
#define CONTROLLER_SEG1 1
#define CONTROLLER_SEG2 2
#define CONTROLLER_SEG3 3
#define CONTROLLER_SEG4 4
#define CONTROLLER_SEG5 5
#define CONTROLLER_SEGM2 6
#define MAIN_CONTROLLER 7

// Serial Interface
#define DEVICE "/dev/ser1"
#define TIME_TO_WAIT 20000

//light code
#define RED 	1
#define YELLOW 	2
#define GREEN	3

//time constants in microsecond
#define ONE_S 1000000
#define HALF_S 500000

#endif /* CONSTANTS_H_ */
