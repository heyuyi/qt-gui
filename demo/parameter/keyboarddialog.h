#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <QDialog>

namespace Ui {
class KeyboardDialog;
}

class KeyboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyboardDialog(QWidget *parent = 0);
    ~KeyboardDialog();

    QString getText(void);

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

    void on_button_A_clicked();

    void on_button_B_clicked();

    void on_button_C_clicked();

    void on_button_D_clicked();

    void on_button_E_clicked();

    void on_button_F_clicked();

    void on_button_G_clicked();

    void on_button_H_clicked();

    void on_button_I_clicked();

    void on_button_J_clicked();

    void on_button_K_clicked();

    void on_button_L_clicked();

    void on_button_M_clicked();

    void on_button_N_clicked();

    void on_button_O_clicked();

    void on_button_P_clicked();

    void on_button_Q_clicked();

    void on_button_R_clicked();

    void on_button_S_clicked();

    void on_button_T_clicked();

    void on_button_U_clicked();

    void on_button_V_clicked();

    void on_button_W_clicked();

    void on_button_X_clicked();

    void on_button_Y_clicked();

    void on_button_Z_clicked();

    void on_button_back_clicked();

private:
    Ui::KeyboardDialog *ui;
};

#endif // KEYBOARDDIALOG_H
