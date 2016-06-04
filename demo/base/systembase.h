#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H

#include <QtCore>

class SystemBase
{
public:
    SystemBase();

protected:
    static const int dialogHeight = 480;
    static const int dialogWidth  = 800;
    static const short reagentNum = 7;
    static const QString path;
    static const QString postfix;
    static const QString serialPort1;
};

#endif // SYSTEMBASE_H
