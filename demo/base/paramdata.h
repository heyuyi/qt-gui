#ifndef PARAMDATA_H
#define PARAMDATA_H

#include <QtGlobal>
#include <QFile>

struct SampleParam
{
    int speed;
    int delay;

    SampleParam() : speed(0), delay(0)
    {
    }
};

struct ReagentParam
{
    bool enable;
    int quantity;
    int speed;
    int delay1;
    int pump;
    int delay2;

    ReagentParam() : enable(false), quantity(0),
        speed(0), delay1(0), pump(0), delay2(0)
    {
    }
};

class ParamData
{
public:
    ParamData(int num);
    ParamData(int num, QFile &file);
    ~ParamData();

    void writeParam(const int num, QFile &file);
    void readParam(const int num, QFile &file);

    SampleParam *pS;
    ReagentParam *pR;
};

#endif // PARAMDATA_H
