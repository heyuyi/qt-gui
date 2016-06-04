#ifndef INPUTEDIT_H
#define INPUTEDIT_H

#include <QLineEdit>

class InputEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit InputEdit(QWidget *parent = 0);

signals:
    void released();
public slots:

protected:
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // INPUTEDIT_H
