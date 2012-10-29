/*
 * SerInterface.h
 *
 *  Created on: Oct 27, 2012
 *      Author: simohamed
 */

#ifndef SERINTERFACE_H_
#define SERINTERFACE_H_
/*
    // open --------------------------------------------------------------------

    // O_NOCTTY:
    // If set, and path identifies a terminal device, the open() function
    // doesn't cause the terminal device to become the controlling terminal for
    // the process.

    int fd = open(device, O_RDWR | O_NOCTTY); // O_NOBLOCK => nicht blockierend
    if (fd < 0) {
        perror(device);
        exit(-1);
    }

    // close -------------------------------------------------------------------

    close(fd);
    fd = 0;

    // write -------------------------------------------------------------------

    ssize_t write( int fd,              // s. open
                   const void* buf,     // Sendepuffer
                   size_t nbytes );     // Anzahl der zu schreibenden Bytes

    usleep(200000);                     // min. Zeit zwischen 2 Nachrichten

    // read --------------------------------------------------------------------

    // Empfangen O_NONBLOCK = 1 (s. open) => nicht blockierend

    ssize_t read( int fd,           // s. open
                  void* buf,        // Empfangspuffer
                  size_t nbyte );   // Anzahl der zu lesenden Bytes

    int readcond( int fd,
                  void * buf,
                  int n,            // Anzahl der max. zu lesenden Bytes
                  int min,          //
                  int time,         // Wartezweit zw. 2 zusammgengehörigen Bytes
                                    // "The pause time ."
                  int timeout );

    // Pause time and timeout "is specified in 1/10 of a second"

    readcond( int fd, void* buf, maxLen, maxLen, // kein min/max
              1, // max. 0.1 Sekunden zwischen 2 zusammengehörigen Bytes
              0  // ohne Timeout blockieren, bis etwas gesendet wurde
    );

    readcond(fd, buf, maxLen, maxLen,
              1, // max. 0.1 Sekunden zwischen 2 zusammengehörigen Bytes
              1  // minimales Blockieren, bis etwas gesendet wurde
        );
    }*/
class SerInterface {
public:
	SerInterface();
	virtual ~SerInterface();
};

#endif /* SERINTERFACE_H_ */
