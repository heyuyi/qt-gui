#include "base/systembase.h"
#include "paramdialog.h"
#include "ui_paramdialog.h"
#include "filelistdialog.h"
#include "keyboarddialog.h"

#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QMessageBox>

ParamDialog::ParamDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint),
    ui(new Ui::ParamDialog),
    nDialog(new NumberDialog(this)), param(NULL),
    name(), treeItem(0), editItem(0), isChanged(false)
{
    ui->setupUi(this);
    setFixedSize(SystemBase::dialogWidth, SystemBase::dialogHeight);
    QPalette pale;
    pale.setBrush(QPalette::Background, QBrush(QPixmap(SystemBase::path + QString("/../resource/base/background.jpg"))));
    setPalette(pale);

    nDialog->move(parent->x()+580, parent->y()+120);
    connect(nDialog, SIGNAL(outValue()), this, SLOT(nDialogOutValueSLOT()));

    ui->newLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/new_up.jpg")));
    ui->openLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/open_up.jpg")));
    ui->saveLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/save_up.jpg")));
    ui->saveAsLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/saveas_up.jpg")));
    ui->confirmLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/confirm_up.jpg")));
    ui->cancelLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/cancel_up.jpg")));

    ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(dateTimerSLOT()));
    timer->start(1000);

    QIcon icon1(QPixmap(SystemBase::path + "/../resource/parameter/treeView1.png"));
    QIcon icon2(QPixmap(SystemBase::path + "/../resource/parameter/treeView2.png"));
    treeModel = new QStandardItemModel(ui->paramView);
    QStandardItem *item1 = new QStandardItem(icon1, QObject::tr("样本过滤设置"));
    treeModel->appendRow(item1);
    QStandardItem *item2 = new QStandardItem(icon1, QObject::tr("试剂设置"));
    treeModel->appendRow(item2);
    QFont font = item1->font();
    font.setPointSize(12);
    item1->setFont(font);
    item2->setFont(font);
    for(int i = 0; i < SystemBase::reagentNum; ++i) {
        QStandardItem *item = new QStandardItem(icon2, QObject::tr("试剂")+QString::number(i+1));
        item->setFont(font);
        item2->appendRow(item);
    }
    ui->paramView->setModel(treeModel);
    ui->paramView->expandAll();

    QDir dir(SystemBase::path);
    if(!dir.exists())
        dir.mkdir(SystemBase::path);
    QFile file(SystemBase::path + QString("/") + SystemBase::postfix);
    if(file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString str = in.readLine();
        QFile f(SystemBase::path + str + QString(".") + SystemBase::postfix);
        if(f.exists()) {
            name = str;
            param = new ParamData(SystemBase::reagentNum, f);
            goto label;
        }
        file.close();
    }
    ui->paramView->setEnabled(false);
    ui->saveLabel->setEnabled(false);
    ui->saveAsLabel->setEnabled(false);
label:
    treeModel->setHorizontalHeaderLabels(QStringList(name));
    displayUpdate();
}

ParamDialog::~ParamDialog()
{
    if(param != NULL)
        delete param;
    delete ui;
}

void ParamDialog::dateTimerSLOT(void)
{
    ui->dateLabel->setText(QDate::currentDate().toString("yyyy/MM/dd"));
}

void ParamDialog::saveCheck(void)
{
    if(param != NULL && isChanged) {
        QFile file(SystemBase::path + name + QString(".") + SystemBase::postfix);
        if(QMessageBox::warning(this, QObject::tr("提示"), QObject::tr("当前配置已经更改，是否保存当前更改？"), QMessageBox::Yes, QMessageBox::No)
                == QMessageBox::Yes) {
            param->writeParam(SystemBase::reagentNum, file);
        } else {
            param->readParam(SystemBase::reagentNum, file);
            displayUpdate();
        }
    }
    isChanged = false;
}

void ParamDialog::displayUpdate(void)
{
    if(param == NULL) {
        ui->sampleBox->setVisible(false);
        ui->reagentBox->setVisible(false);
        return;
    }
    if(treeItem == 0) {
        ui->pumpSpeedEdit->setText(QString::number(param->pS->speed));
        ui->delayEdit->setText(QString::number(param->pS->delay));
        ui->sampleBox->setVisible(true);
        ui->reagentBox->setVisible(false);
    } else {
        if(param->pR[treeItem-1].enable) {
            ui->enableCheckBox->setChecked(true);
            ui->quantityEdit->setEnabled(true);
            ui->quantityEdit->setText(QString::number(param->pR[treeItem-1].quantity));
            ui->speedEdit->setEnabled(true);
            ui->speedEdit->setText(QString::number(param->pR[treeItem-1].speed));
            ui->delay1Edit->setEnabled(true);
            ui->delay1Edit->setText(QString::number(param->pR[treeItem-1].delay1));
            ui->pumpEdit->setEnabled(true);
            ui->pumpEdit->setText(QString::number(param->pR[treeItem-1].pump));
            ui->delay2Edit->setEnabled(true);
            ui->delay2Edit->setText(QString::number(param->pR[treeItem-1].delay2));
        } else {
            ui->enableCheckBox->setChecked(false);
            ui->quantityEdit->setEnabled(false);
            ui->quantityEdit->setText("");
            ui->speedEdit->setEnabled(false);
            ui->speedEdit->setText("");
            ui->delay1Edit->setEnabled(false);
            ui->delay1Edit->setText("");
            ui->pumpEdit->setEnabled(false);
            ui->pumpEdit->setText("");
            ui->delay2Edit->setEnabled(false);
            ui->delay2Edit->setText("");
        }
        ui->sampleBox->setVisible(false);
        ui->reagentBox->setVisible(true);
    }
}

void ParamDialog::nDialogOutValueSLOT()
{
    unsigned char x = nDialog->getValue();
    switch(editItem) {
    case 1:
        ui->pumpSpeedEdit->setText(QString::number(x));
        param->pS->speed = x;
        break;
    case 2:
        ui->delayEdit->setText(QString::number(x));
        param->pS->delay = x;
        break;
    case 3:
        ui->quantityEdit->setText(QString::number(x));
        param->pR[treeItem-1].quantity = x;
        break;
    case 4:
        ui->speedEdit->setText(QString::number(x));
        param->pR[treeItem-1].speed = x;
        break;
    case 5:
        ui->delay1Edit->setText(QString::number(x));
        param->pR[treeItem-1].delay1 = x;
        break;
    case 6:
        ui->pumpEdit->setText(QString::number(x));
        param->pR[treeItem-1].pump = x;
        break;
    case 7:
        ui->delay2Edit->setText(QString::number(x));
        param->pR[treeItem-1].delay2 = x;
        break;
    }
    isChanged = true;
    nDialog->hide();
    editItem = 0;
}

void ParamDialog::on_paramView_clicked(const QModelIndex &index)
{
    nDialog->hide();
    editItem = 0;
    QModelIndex p = index.parent();
    if(p.isValid()) {
        treeItem = index.row()+1;
    } else if(index.row() == 0) {
        treeItem = 0;
    }
    displayUpdate();
}

void ParamDialog::on_enableCheckBox_clicked()
{
    param->pR[treeItem-1].enable = ui->enableCheckBox->isChecked();
    displayUpdate();
    isChanged = true;
}

void ParamDialog::on_pumpSpeedEdit_released()
{
    if(editItem == 1) {
        nDialog->hide();
        editItem = 0;
    } else {
        nDialog->setText(ui->pumpSpeedEdit->text());
        if(editItem == 0)
            nDialog->show();
        editItem = 1;
    }
}

void ParamDialog::on_delayEdit_released()
{
    if(editItem == 2) {
        nDialog->hide();
        editItem = 0;
    } else {
        nDialog->setText(ui->delayEdit->text());
        if(editItem == 0)
            nDialog->show();
        editItem = 2;
    }
}

void ParamDialog::on_quantityEdit_released()
{
    if(editItem == 3) {
        nDialog->hide();
        editItem = 0;
    } else {
        nDialog->setText(ui->quantityEdit->text());
        if(editItem == 0)
            nDialog->show();
        editItem = 3;
    }
}

void ParamDialog::on_speedEdit_released()
{
    if(editItem == 4) {
        nDialog->hide();
        editItem = 0;
    } else {
        nDialog->setText(ui->speedEdit->text());
        if(editItem == 0)
            nDialog->show();
        editItem = 4;
    }
}

void ParamDialog::on_delay1Edit_released()
{
    if(editItem == 5) {
        nDialog->hide();
        editItem = 0;
    } else {
        nDialog->setText(ui->delay1Edit->text());
        if(editItem == 0)
            nDialog->show();
        editItem = 5;
    }
}

void ParamDialog::on_pumpEdit_released()
{
    if(editItem == 6) {
        nDialog->hide();
        editItem = 0;
    } else {
        nDialog->setText(ui->pumpEdit->text());
        if(editItem == 0)
            nDialog->show();
        editItem = 6;
    }
}

void ParamDialog::on_delay2Edit_released()
{
    if(editItem == 7) {
        nDialog->hide();
        editItem = 0;
    } else {
        nDialog->setText(ui->delay2Edit->text());
        if(editItem == 0)
            nDialog->show();
        editItem = 7;
    }
}

void ParamDialog::on_newLabel_pressed()
{
    ui->newLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/new_down.jpg")));
}

void ParamDialog::on_newLabel_released()
{
    saveCheck();
    KeyboardDialog kd(this);
    if(kd.exec() == QDialog::Accepted) {
        if(param != NULL)
            delete param;

        name = kd.getText();
        param = new ParamData(SystemBase::reagentNum);
        treeModel->setHorizontalHeaderLabels(QStringList(name));
        displayUpdate();
        isChanged = true;

        ui->paramView->setEnabled(true);
        ui->saveLabel->setEnabled(true);
        ui->saveAsLabel->setEnabled(true);
    }
    ui->newLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/new_up.jpg")));
}

void ParamDialog::on_openLabel_pressed()
{
    ui->openLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/open_down.jpg")));
}

void ParamDialog::on_openLabel_released()
{
    saveCheck();
    FileListDialog fd(this, SystemBase::path, QString(".") + SystemBase::postfix);
    if(fd.exec() == QDialog::Accepted) {
        name = fd.selectedFile();
        QFile file(SystemBase::path + name + QString(".") + SystemBase::postfix);
        if(param) {
            param->readParam(SystemBase::reagentNum, file);
        } else {
            param = new ParamData(SystemBase::reagentNum, file);
        }
        treeModel->setHorizontalHeaderLabels(QStringList(name));
        displayUpdate();

        ui->paramView->setEnabled(true);
        ui->saveLabel->setEnabled(true);
        ui->saveAsLabel->setEnabled(true);
    }
    ui->openLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/open_up.jpg")));
}

void ParamDialog::on_saveLabel_pressed()
{
    ui->saveLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/save_down.jpg")));
}

void ParamDialog::on_saveLabel_released()
{
    if(param != NULL && isChanged) {
        QFile file(SystemBase::path + name + QString(".") + SystemBase::postfix);
        param->writeParam(SystemBase::reagentNum, file);
        isChanged = false;
    }
    ui->saveLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/save_up.jpg")));
}

void ParamDialog::on_saveAsLabel_pressed()
{
    ui->saveAsLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/saveas_down.jpg")));
}

void ParamDialog::on_saveAsLabel_released()
{
    KeyboardDialog kd(this);
    if(kd.exec() == QDialog::Accepted) {
        name = kd.getText();
        QFile file(SystemBase::path + name + QString(".") + SystemBase::postfix);
        param->writeParam(SystemBase::reagentNum, file);
        treeModel->setHorizontalHeaderLabels(QStringList(name));
        displayUpdate();
        isChanged = false;
    }
    ui->saveAsLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/saveas_up.jpg")));
}

void ParamDialog::on_confirmLabel_pressed()
{
    ui->confirmLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/confirm_down.jpg")));
}

void ParamDialog::on_confirmLabel_released()
{
    saveCheck();
    QFile file(SystemBase::path + QString("/") + SystemBase::postfix);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out << name << endl;
        file.close();
    }
    accept();
//    ui->confirmLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/confirm_up.jpg")));
}

void ParamDialog::on_cancelLabel_pressed()
{
    ui->cancelLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/cancel_down.jpg")));
}

void ParamDialog::on_cancelLabel_released()
{
    ui->cancelLabel->setPixmap(QPixmap(SystemBase::path + QString("/../resource/parameter/cancel_up.jpg")));
}
