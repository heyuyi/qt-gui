#include "timesetdialog.h"
#include "ui_timesetdialog.h"
#include "base/systembase.h"

TimeSetDialog::TimeSetDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::TimeSetDialog), date(QDate::currentDate())
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    ui->confirmLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/base/confirm_up.jpg")));
    ui->cancelLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/base/cancel_up.jpg")));
}

TimeSetDialog::~TimeSetDialog()
{
    delete ui;
}

void TimeSetDialog::on_calendarWidget_clicked(const QDate &date)
{
    this->date = date;
}

void TimeSetDialog::on_confirmLabel_pressed()
{
    ui->confirmLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/base/confirm_down.jpg")));
}

void TimeSetDialog::on_confirmLabel_released()
{
    accept();
}

void TimeSetDialog::on_cancelLabel_pressed()
{
    ui->cancelLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/base/cancel_up.jpg")));
}

void TimeSetDialog::on_cancelLabel_released()
{
    reject();
}

const QDate TimeSetDialog::getDate(void)
{
    return date;
}
