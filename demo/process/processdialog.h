#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H

#include "communication.h"

#include <QDialog>

namespace Ui {
class ProcessDialog;
}

class ProcessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessDialog(QWidget *parent = 0);
    ~ProcessDialog();

    void init(void);

private slots:
    void dateTimerSLOT(void);

    void sendDelaySLOT(void);

    void receDataSLOT(char comm, QByteArray data);

    void on_exitLabel_released();

    void on_outLabel_pressed();

    void on_outLabel_released();

    void on_inLabel_pressed();

    void on_inLabel_released();

    void on_startLabel_pressed();

    void on_startLabel_released();

    void on_cancelLabel_pressed();

    void on_cancelLabel_released();

private:
    Ui::ProcessDialog *ui;
    Communication *comm;
    QTimer *sendDeleyTimer;
    volatile char cmd;
};

#endif // PROCESSDIALOG_H
