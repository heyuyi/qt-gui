#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private slots:
    void startTimerSLOT(void);

    void dateTimerSLOT(void);

    void on_processImage_pressed();

    void on_processImage_released();

    void on_searchImage_pressed();

    void on_searchImage_released();

    void on_paramImage_pressed();

    void on_paramImage_released();

    void on_updateImage_pressed();

    void on_updateImage_released();

    void on_reagentImage_pressed();

    void on_reagentImage_released();

    void on_helpImage_pressed();

    void on_helpImage_released();

    void on_shutdownImage_pressed();

    void on_shutdownImage_released();

    void on_dateLabel_released();

private:
    Ui::MainDialog *ui;
    QTimer *startTimer;
    int startCnt;
};

#endif // MAINDIALOG_H
