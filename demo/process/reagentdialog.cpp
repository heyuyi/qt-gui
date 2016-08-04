#include "reagentdialog.h"
#include "ui_reagentdialog.h"
#include "base/systembase.h"

ReagentDialog::ReagentDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::ReagentDialog)
{
    ui->setupUi(this);
    setFixedSize(SystemBase::dialogWidth, SystemBase::dialogHeight);
    QPalette pale;
    pale.setBrush(QPalette::Background, QBrush(QPixmap(SystemBase::path + QString("/../resource/base/background.jpg"))));
    setPalette(pale);

    ui->pictureLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/00.jpg")));
    ui->changeLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/change_up.jpg")));
    ui->finishLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/finish_up.jpg")));
    ui->confirmLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/confirm_up.jpg")));

    changeTimer = new QTimer(this);
    connect(changeTimer, SIGNAL(timeout()), this, SLOT(changeTimerSLOT()));

    ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(dateTimerSLOT()));
    timer->start(1000);
}

ReagentDialog::~ReagentDialog()
{
    delete ui;
}

void ReagentDialog::dateTimerSLOT(void)
{
    ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
}

void ReagentDialog::changeTimerSLOT(void)
{
    changeCnt++;
    if(changeCnt <= 10)
        ui->pictureLabel->setPixmap(QPixmap(SystemBase::path + "/../resource/reagent/" + QString::number(changeCnt) + "0.jpg"));
    else
        changeTimer->stop();
}

void ReagentDialog::on_changeLabel_pressed()
{
    ui->changeLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/change_down.jpg")));
}

void ReagentDialog::on_changeLabel_released()
{
    changeCnt = 0;
    changeTimer->start(300);
    ui->changeLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/change_up.jpg")));
}

void ReagentDialog::on_finishLabel_pressed()
{
    ui->finishLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/finish_down.jpg")));
}

void ReagentDialog::on_finishLabel_released()
{
    ui->finishLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/finish_up.jpg")));
}

void ReagentDialog::on_confirmLabel_pressed()
{
    ui->confirmLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/confirm_down.jpg")));
}

void ReagentDialog::on_confirmLabel_released()
{
//    ui->confirmLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/reagent/confirm_up.jpg")));
    accept();
}
