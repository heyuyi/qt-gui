#include "processdialog.h"
#include "ui_processdialog.h"

#include <QMessageBox>

ProcessDialog::ProcessDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::ProcessDialog),
    port(new Posix_QextSerialPort(serialPort1)), param(NULL),
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
    if(param != NULL)
        delete param;
    delete ui;
}

bool ProcessDialog::init(void)
{
    QFile file(path + QString("/") + postfix);
    if(file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString str = in.readLine();
        QFile f(path + str + QString(".") + postfix);
        if(f.exists()) {
            param = new ParamData(reagentNum, f);
            goto label;
        }
    }
    QMessageBox::warning((QWidget*)(this->parent()), "提示", "请先进行参数配置!", QMessageBox::Yes);
    return false;

label:
    if(!port->open(QIODevice::ReadWrite)) {
        QMessageBox::warning((QWidget*)(this->parent()), "提示", "无法打开串口!", QMessageBox::Yes);
        return false;
    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readSerialPortSLOT()));
    timer->start(100);
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
