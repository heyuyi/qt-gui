#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H

#include "base/basedialog.h"
#include "communication.h"

namespace Ui {
class ProcessDialog;
}

class ProcessDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit ProcessDialog(QWidget *parent = 0);
    ~ProcessDialog();

    void init(void);

private slots:
    void sendDelaySLOT(void);
    void receDataSLOT(char comm, QByteArray data);
    void on_exitLabel_released();

    void on_openButton_clicked();

private:
    Ui::ProcessDialog *ui;
    Communication *comm;
    QTimer *timer;
    QPixmap icon1, icon2;
    volatile char cmd;
    bool isOpen, toClose;
};

#endif // PROCESSDIALOG_H
