#ifndef NUMBERDIALOG_H
#define NUMBERDIALOG_H

#include <QDialog>

namespace Ui {
class NumberDialog;
}

class NumberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NumberDialog(QWidget *parent = 0);
    ~NumberDialog();

    void setText(const QString &str);
    int getValue(void);

signals:
    void outValue();

private slots:
    void on_button_0_clicked();

    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_button_back_clicked();

    void on_confirm_clicked();

private:
    Ui::NumberDialog *ui;
    QString sbuf;
    unsigned char value;
};

#endif // NUMBERDIALOG_H
