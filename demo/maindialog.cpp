#include "maindialog.h"
#include "ui_maindialog.h"
#include "parameter/paramdialog.h"
#include "process/processdialog.h"

#include <QThread>

MainDialog::MainDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::MainDialog)
{
    ui->setupUi(this);
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::on_resultImage_released()
{
    ui->resultImage->setFrameShadow(QFrame::Sunken);
    ui->resultLabel->setStyleSheet("color: green");
}

void MainDialog::on_processImage_released()
{
    ui->processImage->setFrameShadow(QFrame::Sunken);
    ui->processLabel->setStyleSheet("color: green");
    ProcessDialog pProc(this);
    if(pProc.exec() == QDialog::Accepted) {

    }
    ui->processImage->setFrameShadow(QFrame::Raised);
    ui->processLabel->setStyleSheet("color: black");
}

void MainDialog::on_paramImage_released()
{
    ui->paramImage->setFrameShadow(QFrame::Sunken);
    ui->paramLabel->setStyleSheet("color: green");
    ParamDialog pParam(this);
    if(pParam.exec() == QDialog::Accepted) {

    }
    ui->paramImage->setFrameShadow(QFrame::Raised);
    ui->paramLabel->setStyleSheet("color: black");
}
