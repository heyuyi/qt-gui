#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QThread>

class Communication : public QThread
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = 0);

signals:

public slots:

};

#endif // COMMUNICATION_H
