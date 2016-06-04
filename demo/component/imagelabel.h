#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>

class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = 0);

signals:
    void released();
public slots:

protected:
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // IMAGELABEL_H
