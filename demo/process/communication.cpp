#include "communication.h"
#include "base/systembase.h"
#include "base/paramdata.h"

Communication::Communication()
{
}

void Communication::sendData(Posix_QextSerialPort *port,
                             unsigned char comm, void* data)
{
    char buf[100];
    int num = 0;
    buf[num++] = 0xff;
    buf[num++] = 0xff;
    buf[num++] = comm;
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
    buf[num++] = 0xfe;
    port->write(buf, num);
}
