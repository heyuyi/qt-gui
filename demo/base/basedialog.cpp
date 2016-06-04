#include "basedialog.h"
#include "ui_basedialog.h"

#include <QDate>
#include <QTimer>

BaseDialog::BaseDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::BaseDialog)
{
    ui->setupUi(this);
    setFixedSize(dialogWidth, dialogHeight);

    ui->dateLabel->setStyleSheet("color: white");
    ui->dateLabel->setText(QDate::currentDate().toString("yyyy / MM / dd"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(dateTimerSLOT()));
    timer->start(1000);
}

BaseDialog::~BaseDialog()
{
    delete ui;
}

void BaseDialog::dateTimerSLOT(void)
{
    ui->dateLabel->setText(QDate::currentDate().toString("yyyy / MM / dd"));
}
