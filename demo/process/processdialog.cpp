#include "processdialog.h"
#include "ui_processdialog.h"
#include "base/paramdata.h"
#include <QMessageBox>

ProcessDialog::ProcessDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::ProcessDialog),
    icon1(QString::fromUtf8(":/process/stepicon1.png")),
    icon2(QString::fromUtf8(":/process/stepicon2.png")),
    cmd(0xff)
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
    }
}

void ProcessDialog::receDataSLOT(char comm, QByteArray data)
{
    if(comm == 0x00 && cmd == 0x00) {
        timer->stop();
        ui->exitLabel->setVisible(true);
        cmd = 0xff;
    }
}

void ProcessDialog::on_exitLabel_released()
{
    comm->stop();
    reject();
}
