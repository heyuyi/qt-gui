#include "processdialog.h"
#include "ui_processdialog.h"
#include "communication.h"

#include <QMessageBox>

ProcessDialog::ProcessDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::ProcessDialog),
    port(new Posix_QextSerialPort(SystemBase::serialPort1)),
    icon1(QString::fromUtf8(":/process/stepicon1.png")),
    icon2(QString::fromUtf8(":/process/stepicon2.png"))
{
    ui->setupUi(this);
    ui->lcdNumber1->setStyleSheet("background-color: white");
    ui->lcdNumber2->setStyleSheet("background-color: white");
    ui->lcdNumber3->setStyleSheet("background-color: white");

    ui->stepImage_1->setPixmap(icon2);

    port->setBaudRate(BAUD115200);
    port->setDataBits(DATA_8);
    port->setParity(PAR_NONE);
    port->setStopBits(STOP_1);
    port->setFlowControl(FLOW_OFF);
    port->setTimeout(0, 10);
}

ProcessDialog::~ProcessDialog()
{
    delete port;
    delete ui;
}

bool ProcessDialog::init(void)
{
    if(!port->open(QIODevice::ReadWrite)) {
        QMessageBox::warning((QWidget*)(this->parent()), "提示", "无法打开串口!", QMessageBox::Yes);
        return false;
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
    QMessageBox::warning((QWidget*)(this->parent()), "提示", "请先进行参数配置!", QMessageBox::Yes);
    return false;

label:
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readSerialPortSLOT()));
    timer->start(100);

    Communication::sendData(port, 0x00, param);

    delete param;
    return true;
}

void ProcessDialog::readSerialPortSLOT(void)
{
//    QByteArray data = port->readAll();
}

void ProcessDialog::on_exitLabel_released()
{
    if(port->isOpen())
        port->close();
    reject();
}
