#include "processdialog.h"
#include "ui_processdialog.h"
#include "base/paramdata.h"
#include <QMessageBox>

ProcessDialog::ProcessDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::ProcessDialog),
    icon1(QString::fromUtf8(":/process/stepicon1.png")),
    icon2(QString::fromUtf8(":/process/stepicon2.png")),
    cmd(0xff), isOpen(false), toClose(false)
{
    ui->setupUi(this);
    comm = new Communication(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendDelaySLOT()));
    connect(comm, SIGNAL(received(char, QByteArray)), this, SLOT(receDataSLOT(char, QByteArray)));

    ui->lcdNumber1->setStyleSheet("background-color: white");
    ui->lcdNumber2->setStyleSheet("background-color: white");
    ui->lcdNumber3->setStyleSheet("background-color: white");

    ui->stepImage_1->setPixmap(icon2);

    ui->exitLabel->setVisible(false);
    ui->openButton->setVisible(false);
}

ProcessDialog::~ProcessDialog()
{
    delete ui;
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
    timer->start(1000);
    delete param;
    exec();
}

void ProcessDialog::sendDelaySLOT(void)
{
    if(cmd == 0x00) {
        QMessageBox::warning(this, QObject::tr("警告"), QObject::tr("与下位机连接失败!"), QMessageBox::Yes);
        timer->stop();
        comm->stop();
        reject();
    } else {
        QMessageBox::warning(this, QObject::tr("警告"), QObject::tr("与下位机通讯失败!"), QMessageBox::Yes);
        timer->stop();
    }
}

void ProcessDialog::receDataSLOT(char comm, QByteArray data)
{
    timer->stop();
    if(comm == 0x01 && cmd == 0x00) {
        ui->exitLabel->setVisible(true);
        ui->openButton->setVisible(true);
    } else if(comm == 0x03 && cmd == 0x02) {
        isOpen = true;
        ui->openButton->setText(QObject::tr("进仓"));
    } else if(comm == 0x05 && cmd == 0x04) {
        isOpen = false;
        ui->openButton->setText(QObject::tr("出仓"));
    }
    cmd = 0xff;
}

void ProcessDialog::on_exitLabel_released()
{
    comm->stop();
    reject();
}

void ProcessDialog::on_openButton_clicked()
{
    if(isOpen)
        cmd = 0x04;
    else
        cmd = 0x02;
    comm->sendData(cmd, NULL);
    timer->start(1000);
}
