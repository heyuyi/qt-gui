#include "communication.h"
#include "base/systembase.h"
#include "base/paramdata.h"

#include <QTimer>

Communication::Communication(QObject *parent) :
    QObject(parent), port(new Posix_QextSerialPort(SystemBase::serialPort3)),
    array(), running(true)
{
    port->setBaudRate(BAUD115200);
    port->setDataBits(DATA_8);
    port->setParity(PAR_NONE);
    port->setStopBits(STOP_1);
    port->setFlowControl(FLOW_OFF);
    port->setTimeout(0, 10);
}

Communication::~Communication()
{
    delete port;
}

bool Communication::setup(void)
{
    if(!port->open(QIODevice::ReadWrite))
        return false;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readSerialPortSLOT()));
    timer->start(100);
    return true;
}

void Communication::stop(void)
{
    port->close();
    running = false;
}

void Communication::sendData(unsigned char comm, void* data)
{
    char buf[50];
    int num = 2;
    buf[0] = 0xff;
    buf[1] = comm;
    if(comm == 0x00) {
        ParamData *param = (ParamData *)data;
        buf[num++] = 44;
        buf[num++] = param->pS->speed;
        buf[num++] = param->pS->delay;
        for(int i = 0; i < SystemBase::reagentNum; ++i) {
            buf[num++] = param->pR[i].enable;
            buf[num++] = param->pR[i].quantity;
            buf[num++] = param->pR[i].speed;
            buf[num++] = param->pR[i].delay1;
            buf[num++] = param->pR[i].pump;
            buf[num++] = param->pR[i].delay2;
        }
    } else if(comm == 0x02) {
        unsigned char *p = (unsigned char *)data;
        buf[num++] = 1;
        buf[num++] = *p;
    }
    port->write(buf, num);
}

void Communication::readSerialPortSLOT(void)
{
    array += port->readAll();
//  char a[] = {0xff, 0x01, 0x02, 0xff, 0x01, 0x02, 0xff, 0x01, 0x02};
//  array += a;
    QList<QByteArray> arrays = array.split(0xff);
    int n = arrays.size()-1;
    for(int i = 1; i < n; ++i) {
        int m = arrays[i].size();
        if(m < 2)
            continue;
        if((arrays[i][1]+2) != m)
            continue;

    }
    array = QByteArray(1, 0xff) + arrays.last();
}
