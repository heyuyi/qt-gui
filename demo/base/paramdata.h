#ifndef PARAMDATA_H
#define PARAMDATA_H

#include <QFile>

struct SampleParam
{
    unsigned char speed;
    unsigned char delay;

    SampleParam() : speed(0), delay(0)
    {
    }
};

struct ReagentParam
{
    unsigned char enable;
    unsigned char quantity;
    unsigned char speed;
    unsigned char delay1;
    unsigned char pump;
    unsigned char delay2;

    ReagentParam() : enable(0), quantity(0),
        speed(0), delay1(0), pump(0), delay2(0)
    {
    }
};

class ParamData
{
public:
    ParamData(const int num);
    ParamData(const int num, QFile &file);
    ~ParamData();

    void writeParam(const int num, QFile &file);
    void readParam(const int num, QFile &file);

    SampleParam *pS;
    ReagentParam *pR;
};

#endif // PARAMDATA_H
