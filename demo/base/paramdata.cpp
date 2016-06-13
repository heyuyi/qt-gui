#include "paramdata.h"

#include <QTextStream>

ParamData::ParamData(const int num) :
    pS(new SampleParam), pR(new ReagentParam[num])
{
}

ParamData::ParamData(const int num, QFile &file) :
    pS(new SampleParam), pR(new ReagentParam[num])
{
    readParam(num, file);
}

ParamData::~ParamData()
{
    delete pS;
    delete[] pR;
}

void ParamData::writeParam(const int num, QFile &file)
{
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out << pS->speed << ',' << pS->delay << endl;
        for(int i = 0; i < num; ++i)
            out << pR[i].enable << ',' << pR[i].quantity << ',' << pR[i].speed << ',' <<
                   pR[i].delay1 << ',' << pR[i].pump << ',' << pR[i].delay2 << endl;
        file.close();
    }
}

void ParamData::readParam(const int num, QFile &file)
{
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString str = in.readLine();
        bool flag;
        if(!str.isEmpty()) {
            QStringList strlist = str.split(",");
            if(strlist.size() >= 1)
                pS->speed = strlist.at(0).toUShort(&flag, 10);
            if(strlist.size() >= 2)
                pS->delay = strlist.at(1).toUShort(&flag, 10);
        }
        for(int i = 0; i < num; ++i) {
            str = in.readLine();
            if(str.isEmpty())
                break;
            QStringList strlist = str.split(",");
            if(strlist.size() >= 1)
                pR[i].enable = strlist.at(0).toUShort(&flag, 10);
            if(strlist.size() >= 2)
                pR[i].quantity = strlist.at(1).toUShort(&flag, 10);
            if(strlist.size() >= 3)
                pR[i].speed = strlist.at(2).toUShort(&flag, 10);
            if(strlist.size() >= 4)
                pR[i].delay1 = strlist.at(3).toUShort(&flag, 10);
            if(strlist.size() >= 5)
                pR[i].pump = strlist.at(4).toUShort(&flag, 10);
            if(strlist.size() >= 6)
                pR[i].delay2 = strlist.at(5).toUShort(&flag, 10);
        }
        file.close();
    }
}
