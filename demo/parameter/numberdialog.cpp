#include "numberdialog.h"
#include "ui_numberdialog.h"

#include <QMessageBox>

NumberDialog::NumberDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::NumberDialog),
    sbuf(), value(0)
{
    ui->setupUi(this);
    setModal(false);
    setFixedSize(this->width(), this->height());
}

NumberDialog::~NumberDialog()
{
    delete ui;
}

void NumberDialog::setText(const QString &str)
{
    sbuf = str;
    ui->text->setText(str);
}

int NumberDialog::getValue()
{
    return value;
}

void NumberDialog::on_button_0_clicked()
{
    ui->text->setText(ui->text->text()+'0');
}

void NumberDialog::on_button_1_clicked()
{
    ui->text->setText(ui->text->text()+'1');
}

void NumberDialog::on_button_2_clicked()
{
    ui->text->setText(ui->text->text()+'2');
}

void NumberDialog::on_button_3_clicked()
{
    ui->text->setText(ui->text->text()+'3');
}

void NumberDialog::on_button_4_clicked()
{
    ui->text->setText(ui->text->text()+'4');
}

void NumberDialog::on_button_5_clicked()
{
    ui->text->setText(ui->text->text()+'5');
}

void NumberDialog::on_button_6_clicked()
{
    ui->text->setText(ui->text->text()+'6');
}

void NumberDialog::on_button_7_clicked()
{
    ui->text->setText(ui->text->text()+'7');
}

void NumberDialog::on_button_8_clicked()
{
    ui->text->setText(ui->text->text()+'8');
}

void NumberDialog::on_button_9_clicked()
{
    ui->text->setText(ui->text->text()+'9');
}

void NumberDialog::on_button_back_clicked()
{
    QString str = ui->text->text();
    if(!str.isEmpty())
        ui->text->setText(str.left(str.size()-1));
}

void NumberDialog::on_confirm_clicked()
{
    bool flag;
    ushort x = ui->text->text().toUShort(&flag, 10);
    if(flag && x <= 255) {
        value = x;
        emit outValue();
    } else {
        QMessageBox::warning(this, QObject::tr("提示"), QObject::tr("当前输入非法"), QMessageBox::Yes);
        ui->text->setText(sbuf);
    }
}
