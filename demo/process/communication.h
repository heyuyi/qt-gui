#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "qextserialport/posix_qextserialport.h"

class Communication : public QObject
{
    Q_OBJECT

public:
    explicit Communication(QObject *parent = 0);
    ~Communication();

    bool setup(void);
    void stop(void);
    void sendData(unsigned char comm, void* data);

signals:

private slots:
    void readSerialPortSLOT(void);

private:
    Posix_QextSerialPort *port;
    QByteArray array;
    volatile bool running;
};

#endif // COMMUNICATION_H
