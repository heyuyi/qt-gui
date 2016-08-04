#ifndef TIMESETDIALOG_H
#define TIMESETDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class TimeSetDialog;
}

class TimeSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeSetDialog(QWidget *parent = 0);
    ~TimeSetDialog();

    const QDate getDate(void);
private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_confirmLabel_pressed();

    void on_confirmLabel_released();

    void on_cancelLabel_pressed();

    void on_cancelLabel_released();

private:
    Ui::TimeSetDialog *ui;
    QDate date;
};

#endif // TIMESETDIALOG_H
