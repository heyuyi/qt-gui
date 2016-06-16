#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H

#include "base/basedialog.h"
#include "base/paramdata.h"
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

    bool init(void);

private slots:
    void on_exitLabel_released();

private:
    Ui::ProcessDialog *ui;
    Communication *comm;
    QPixmap icon1, icon2;
};

#endif // PROCESSDIALOG_H
