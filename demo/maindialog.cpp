#include "maindialog.h"
#include "ui_maindialog.h"
#include "base/systembase.h"
#include "base/timesetdialog.h"
#include "parameter/paramdialog.h"
#include "process/processdialog.h"
#include "process/reagentdialog.h"

#include <QThread>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::MainDialog), startCnt(1)
{
    ui->setupUi(this);
    setFixedSize(SystemBase::dialogWidth, SystemBase::dialogHeight);
    QPalette pale;
    pale.setBrush(QPalette::Background, QBrush(QPixmap(SystemBase::path + QString("/../resource/base/background.jpg"))));
    setPalette(pale);

    ui->processImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/process_up.jpg")));
    ui->searchImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/search_up.jpg")));
    ui->paramImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/param_up.jpg")));
    ui->updateImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/update_up.jpg")));
    ui->reagentImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/reagent_up.jpg")));
    ui->helpImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/help_up.jpg")));
    ui->shutdownImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/shutdown_up.jpg")));
    ui->processImage->setVisible(false);
    ui->searchImage->setVisible(false);
    ui->paramImage->setVisible(false);
    ui->updateImage->setVisible(false);
    ui->reagentImage->setVisible(false);
    ui->helpImage->setVisible(false);
    ui->shutdownImage->setVisible(false);

    ui->startImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/start10.jpg")));
    ui->startLabel->setText("10%");
    ui->startLabel->setStyleSheet("color: white");

    startTimer = new QTimer(this);
    connect(startTimer, SIGNAL(timeout()), this, SLOT(startTimerSLOT()));
    startTimer->start(300);

    ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(dateTimerSLOT()));
    timer->start(1000);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::startTimerSLOT(void)
{
    if(startCnt < 10) {
        startCnt++;
        QString x = QString::number(startCnt);
        ui->startImage->setPixmap(QPixmap(SystemBase::path+QString("/../resource/main/start")+x+QString("0.jpg")));
        ui->startLabel->setText(x+"0%");
    } else {
        startTimer->stop();
        ui->startImage->setVisible(false);
        ui->startLabel->setVisible(false);

        ui->processImage->setVisible(true);
        ui->searchImage->setVisible(true);
        ui->paramImage->setVisible(true);
        ui->updateImage->setVisible(true);
        ui->reagentImage->setVisible(true);
        ui->helpImage->setVisible(true);
        ui->shutdownImage->setVisible(true);
    }
}

void MainDialog::dateTimerSLOT(void)
{
    ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
}

void MainDialog::on_processImage_pressed()
{
    ui->processImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/process_down.jpg")));
}

void MainDialog::on_processImage_released()
{
    ProcessDialog pProc(this);
    pProc.init();
    ui->processImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/process_up.jpg")));
}

void MainDialog::on_searchImage_pressed()
{
    ui->searchImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/search_down.jpg")));
}

void MainDialog::on_searchImage_released()
{
    ui->searchImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/search_up.jpg")));
}

void MainDialog::on_paramImage_pressed()
{
    ui->paramImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/param_down.jpg")));
}

void MainDialog::on_paramImage_released()
{
    ParamDialog pParam(this);
    if(pParam.exec() == QDialog::Accepted) {

    }
    ui->paramImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/param_up.jpg")));
}

void MainDialog::on_updateImage_pressed()
{
    ui->updateImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/update_down.jpg")));
}

void MainDialog::on_updateImage_released()
{
    ui->updateImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/update_up.jpg")));
}

void MainDialog::on_reagentImage_pressed()
{
    ui->reagentImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/reagent_down.jpg")));
}

void MainDialog::on_reagentImage_released()
{
    ReagentDialog dlg(this);
    dlg.exec();
    ui->reagentImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/reagent_up.jpg")));
}

void MainDialog::on_helpImage_pressed()
{
    ui->helpImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/help_down.jpg")));
}

void MainDialog::on_helpImage_released()
{
    ui->helpImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/help_up.jpg")));
}

void MainDialog::on_shutdownImage_pressed()
{
    ui->shutdownImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/shutdown_down.jpg")));
}

void MainDialog::on_shutdownImage_released()
{
    ui->shutdownImage->setPixmap(QPixmap(SystemBase::path + QString("/../resource/main/shutdown_up.jpg")));
}

void MainDialog::on_dateLabel_released()
{
    TimeSetDialog dlg(this);
    dlg.move(this->x()+315, this->y()+70);
    if(dlg.exec() == QDialog::Accepted) {
        const QDate date = dlg.getDate();
        ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
    }
}
