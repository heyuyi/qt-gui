#ifndef REAGENTDIALOG_H
#define REAGENTDIALOG_H

#include <QDialog>

namespace Ui {
class ReagentDialog;
}

class ReagentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReagentDialog(QWidget *parent = 0);
    ~ReagentDialog();

private slots:
    void dateTimerSLOT(void);

    void changeTimerSLOT(void);

    void on_changeLabel_pressed();

    void on_changeLabel_released();

    void on_finishLabel_pressed();

    void on_finishLabel_released();

    void on_confirmLabel_pressed();

    void on_confirmLabel_released();

private:
    Ui::ReagentDialog *ui;
    QTimer *changeTimer;
    int changeCnt;
};

#endif // REAGENTDIALOG_H
