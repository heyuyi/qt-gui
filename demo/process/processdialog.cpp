#include "processdialog.h"
#include "ui_processdialog.h"
#include "base/paramdata.h"
#include "base/systembase.h"

#include <QMessageBox>

ProcessDialog::ProcessDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::ProcessDialog), cmd(0xff)
{
    ui->setupUi(this);
    setFixedSize(SystemBase::dialogWidth, SystemBase::dialogHeight);
    QPalette pale;
    pale.setBrush(QPalette::Background, QBrush(QPixmap(SystemBase::path + QString("/../resource/base/background.jpg"))));
    setPalette(pale);

    comm = new Communication(this);
    sendDeleyTimer = new QTimer(this);
    connect(sendDeleyTimer, SIGNAL(timeout()), this, SLOT(sendDelaySLOT()));
    connect(comm, SIGNAL(received(char, QByteArray)), this, SLOT(receDataSLOT(char, QByteArray)));

    ui->lcdNumber1->setStyleSheet("background-color: white");
    ui->lcdNumber2->setStyleSheet("background-color: white");
    ui->lcdNumber3->setStyleSheet("background-color: white");

    ui->exitLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/exit.png")));
    ui->picture->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/picture1.jpg")));
    ui->stepImage_1->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/stepicon1.png")));
    ui->stepImage_2->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/stepicon1.png")));
    ui->stepImage_3->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/stepicon1.png")));
    ui->stepImage_4->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/stepicon1.png")));
    ui->stepImage_5->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/stepicon1.png")));
    ui->stepImage_6->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/stepicon1.png")));
    ui->stepImage_7->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/stepicon1.png")));
    ui->stepImage_8->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/stepicon1.png")));
    ui->stepImage_9->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/stepicon1.png")));

    ui->outLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/out_up.jpg")));
    ui->inLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/in_up.jpg")));
    ui->startLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/start_up.jpg")));
    ui->cancelLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/cancel_up.jpg")));
    ui->outLabel->setVisible(true);
    ui->inLabel->setVisible(true);
    ui->startLabel->setVisible(true);
    ui->cancelLabel->setVisible(true);

    ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(dateTimerSLOT()));
    timer->start(1000);
}

ProcessDialog::~ProcessDialog()
{
    delete ui;
}

void ProcessDialog::dateTimerSLOT(void)
{
    ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
}

void ProcessDialog::init(void)
{
    if(!comm->setup()) {
        QMessageBox::warning((QWidget*)(this->parent()), QObject::tr("警告"), QObject::tr("无法打开串口!"), QMessageBox::Yes);
        return;
    }

    ParamData *param;
    QFile file(SystemBase::path + QString("/") + SystemBase::postfix);
    if(file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString str = in.readLine();
        QFile f(SystemBase::path + str + QString(".") + SystemBase::postfix);
        if(f.exists()) {
            param = new ParamData(SystemBase::reagentNum, f);
            goto label;
        }
    }
    QMessageBox::warning((QWidget*)(this->parent()), QObject::tr("警告"), QObject::tr("请先进行参数配置!"), QMessageBox::Yes);
    comm->stop();
    return;

label:
    cmd = 0x00;
    comm->sendData(0x00, param);
    sendDeleyTimer->start(1000);
    delete param;
    exec();
}

void ProcessDialog::sendDelaySLOT(void)
{
    if(cmd == 0x00) {
        QMessageBox::warning(this, QObject::tr("警告"), QObject::tr("与下位机连接失败!"), QMessageBox::Yes);
        sendDeleyTimer->stop();
        comm->stop();
        reject();
    } else {
        QMessageBox::warning(this, QObject::tr("警告"), QObject::tr("与下位机通讯失败!"), QMessageBox::Yes);
        sendDeleyTimer->stop();
    }
}

void ProcessDialog::receDataSLOT(char comm, QByteArray data)
{
    if(comm == 0x01 && cmd == 0x00) {
        sendDeleyTimer->stop();
        ui->outLabel->setVisible(true);
        ui->inLabel->setVisible(true);
        ui->startLabel->setVisible(true);
        ui->cancelLabel->setVisible(true);
    } else if(comm == 0x03 && cmd == 0x02) {
        sendDeleyTimer->stop();
    } else if(comm == 0x05 && cmd == 0x04) {
        sendDeleyTimer->stop();
    } else if(comm == 0x11 && cmd == 0x10) {
        QMessageBox::information(this, QObject::tr("提示"), QObject::tr("流程已运行完成!"), QMessageBox::Yes);
    } else if(comm == 0x07) {
        sendDeleyTimer->stop();
        QMessageBox::warning(this, QObject::tr("警告"), QObject::tr("加样管未检测到!"), QMessageBox::Yes);
    } else if(comm == 0x09) {
        sendDeleyTimer->stop();
        QMessageBox::warning(this, QObject::tr("警告"), QObject::tr("废液槽检测不存在!"), QMessageBox::Yes);
    } else if(comm == 0x0b) {
        sendDeleyTimer->stop();
        QMessageBox::warning(this, QObject::tr("警告"), QObject::tr("试剂槽未归位!"), QMessageBox::Yes);
    } else if(comm == 0x0d) {
        sendDeleyTimer->stop();
        QMessageBox::warning(this, QObject::tr("警告"), QObject::tr("废液槽满!"), QMessageBox::Yes);
    }
    cmd = 0xff;
}

void ProcessDialog::on_exitLabel_released()
{
    comm->stop();
    reject();
}

void ProcessDialog::on_outLabel_pressed()
{
    ui->outLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/out_down.jpg")));
}

void ProcessDialog::on_outLabel_released()
{
    cmd = 0x02;
    comm->sendData(0x02, NULL);
    sendDeleyTimer->start(1000);
    ui->outLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/out_up.jpg")));
}

void ProcessDialog::on_inLabel_pressed()
{
    ui->inLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/in_down.jpg")));
}

void ProcessDialog::on_inLabel_released()
{
    cmd = 0x04;
    comm->sendData(0x04, NULL);
    sendDeleyTimer->start(1000);
    ui->inLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/in_up.jpg")));
}

void ProcessDialog::on_startLabel_pressed()
{
    ui->startLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/start_down.jpg")));
}

void ProcessDialog::on_startLabel_released()
{
    cmd = 0x10;
    comm->sendData(0x10, NULL);
//    timer->start(1000);
    ui->startLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/start_up.jpg")));
}

void ProcessDialog::on_cancelLabel_pressed()
{
    ui->cancelLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/cancel_down.jpg")));
}

void ProcessDialog::on_cancelLabel_released()
{
    QMessageBox::warning(this, QObject::tr("警告"), QObject::tr("确定取消分离染色？确定后分离染色将作废！"), QMessageBox::Yes, QMessageBox::No);
    ui->cancelLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/process/cancel_up.jpg")));
}
