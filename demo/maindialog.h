#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "base/basedialog.h"

namespace Ui {
class MainDialog;
}

class MainDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private slots:
    void on_resultImage_released();
    void on_processImage_released();
    void on_paramImage_released();

private:
    Ui::MainDialog *ui;
};

#endif // MAINDIALOG_H
