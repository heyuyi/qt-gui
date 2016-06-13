#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "qextserialport/posix_qextserialport.h"

class Communication
{
public:
    Communication();

    static void sendData(Posix_QextSerialPort *port,
                         unsigned char comm, void* data);
};

#endif // COMMUNICATION_H
