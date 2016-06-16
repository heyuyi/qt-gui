#include "keyboarddialog.h"
#include "ui_keyboarddialog.h"

#include <QMessageBox>

KeyboardDialog::KeyboardDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::KeyboardDialog)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    move(parent->x()+10, parent->y()+100);
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

KeyboardDialog::~KeyboardDialog()
{
    delete ui;
}

QString KeyboardDialog::getText(void)
{
    return ui->text->text();
}

void KeyboardDialog::on_button_0_clicked()
{
    ui->text->setText(ui->text->text()+'0');
}

void KeyboardDialog::on_button_1_clicked()
{
    ui->text->setText(ui->text->text()+'1');
}

void KeyboardDialog::on_button_2_clicked()
{
    ui->text->setText(ui->text->text()+'2');
}

void KeyboardDialog::on_button_3_clicked()
{
    ui->text->setText(ui->text->text()+'3');
}

void KeyboardDialog::on_button_4_clicked()
{
    ui->text->setText(ui->text->text()+'4');
}

void KeyboardDialog::on_button_5_clicked()
{
    ui->text->setText(ui->text->text()+'5');
}

void KeyboardDialog::on_button_6_clicked()
{
    ui->text->setText(ui->text->text()+'6');
}

void KeyboardDialog::on_button_7_clicked()
{
    ui->text->setText(ui->text->text()+'7');
}

void KeyboardDialog::on_button_8_clicked()
{
    ui->text->setText(ui->text->text()+'8');
}

void KeyboardDialog::on_button_9_clicked()
{
    ui->text->setText(ui->text->text()+'9');
}

void KeyboardDialog::on_button_A_clicked()
{
    ui->text->setText(ui->text->text()+'a');
}

void KeyboardDialog::on_button_B_clicked()
{
    ui->text->setText(ui->text->text()+'b');
}

void KeyboardDialog::on_button_C_clicked()
{
    ui->text->setText(ui->text->text()+'c');
}

void KeyboardDialog::on_button_D_clicked()
{
    ui->text->setText(ui->text->text()+'d');
}

void KeyboardDialog::on_button_E_clicked()
{
    ui->text->setText(ui->text->text()+'e');
}

void KeyboardDialog::on_button_F_clicked()
{
    ui->text->setText(ui->text->text()+'f');
}

void KeyboardDialog::on_button_G_clicked()
{
    ui->text->setText(ui->text->text()+'g');
}

void KeyboardDialog::on_button_H_clicked()
{
    ui->text->setText(ui->text->text()+'h');
}

void KeyboardDialog::on_button_I_clicked()
{
    ui->text->setText(ui->text->text()+'i');
}

void KeyboardDialog::on_button_J_clicked()
{
    ui->text->setText(ui->text->text()+'j');
}

void KeyboardDialog::on_button_K_clicked()
{
    ui->text->setText(ui->text->text()+'k');
}

void KeyboardDialog::on_button_L_clicked()
{
    ui->text->setText(ui->text->text()+'l');
}

void KeyboardDialog::on_button_M_clicked()
{
    ui->text->setText(ui->text->text()+'m');
}

void KeyboardDialog::on_button_N_clicked()
{
    ui->text->setText(ui->text->text()+'n');
}

void KeyboardDialog::on_button_O_clicked()
{
    ui->text->setText(ui->text->text()+'o');
}

void KeyboardDialog::on_button_P_clicked()
{
    ui->text->setText(ui->text->text()+'p');
}

void KeyboardDialog::on_button_Q_clicked()
{
    ui->text->setText(ui->text->text()+'q');
}

void KeyboardDialog::on_button_R_clicked()
{
    ui->text->setText(ui->text->text()+'r');
}

void KeyboardDialog::on_button_S_clicked()
{
    ui->text->setText(ui->text->text()+'s');
}

void KeyboardDialog::on_button_T_clicked()
{
    ui->text->setText(ui->text->text()+'t');
}

void KeyboardDialog::on_button_U_clicked()
{
    ui->text->setText(ui->text->text()+'u');
}

void KeyboardDialog::on_button_V_clicked()
{
    ui->text->setText(ui->text->text()+'v');
}

void KeyboardDialog::on_button_W_clicked()
{
    ui->text->setText(ui->text->text()+'w');
}

void KeyboardDialog::on_button_X_clicked()
{
    ui->text->setText(ui->text->text()+'x');
}

void KeyboardDialog::on_button_Y_clicked()
{
    ui->text->setText(ui->text->text()+'y');
}

void KeyboardDialog::on_button_Z_clicked()
{
    ui->text->setText(ui->text->text()+'z');
}

void KeyboardDialog::on_button_back_clicked()
{
    QString str = ui->text->text();
    if(!str.isEmpty())
        ui->text->setText(str.left(str.size()-1));
}

void KeyboardDialog::on_confirm_clicked()
{
    QString str = ui->text->text();
    if(str.isEmpty())
        QMessageBox::warning(this, "提示", "文件名不能为空！", QMessageBox::Yes);
    else
        accept();
}
