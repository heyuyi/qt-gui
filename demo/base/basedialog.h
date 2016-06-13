#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include "systembase.h"

#include <QDialog>

namespace Ui {
class BaseDialog;
}

class BaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseDialog(QWidget *parent = 0);
    ~BaseDialog();

private slots:
    void dateTimerSLOT(void);

private:
    Ui::BaseDialog *ui;
};

#endif // BASEDIALOG_H
