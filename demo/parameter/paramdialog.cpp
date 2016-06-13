#include "paramdialog.h"
#include "ui_paramdialog.h"
#include "filelistdialog.h"
#include "keyboarddialog.h"

#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QMessageBox>

ParamDialog::ParamDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::ParamDialog),
    nDialog(new NumberDialog(this)), param(NULL),
    name(), treeItem(0), editItem(0), isChanged(false)
{
    ui->setupUi(this);
    nDialog->move(parent->x()+560, parent->y()+130);
    connect(nDialog, SIGNAL(outValue()), this, SLOT(nDialogOutValueSLOT()));

    QIcon icon1(":/param/treeView1.png");
    QIcon icon2(":/param/treeView2.png");
    treeModel = new QStandardItemModel(ui->paramView);
    QStandardItem *item1 = new QStandardItem(icon1, "样本过滤设置");
    treeModel->appendRow(item1);
    QStandardItem *item2 = new QStandardItem(icon1, "试剂设置");
    treeModel->appendRow(item2);
    QFont font = item1->font();
    font.setPointSize(12);
    item1->setFont(font);
    item2->setFont(font);
    for(int i = 0; i < SystemBase::reagentNum; ++i) {
        QStandardItem *item = new QStandardItem(icon2, QStringLiteral("试剂%1").arg(i+1));
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
    ui->saveButton->setEnabled(false);
    ui->saveAsButton->setEnabled(false);
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

void ParamDialog::saveCheck(void)
{
    if(param != NULL && isChanged) {
        QFile file(SystemBase::path + name + QString(".") + SystemBase::postfix);
        if(QMessageBox::warning(this, "提示", "当前配置已经更改，是否保存当前更改？", QMessageBox::Yes, QMessageBox::No)
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
    } else {
        treeItem = 0;
    }
    displayUpdate();
}

void ParamDialog::on_newButton_clicked()
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
        ui->saveButton->setEnabled(true);
        ui->saveAsButton->setEnabled(true);
    }
}

void ParamDialog::on_openButton_clicked()
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
        ui->saveButton->setEnabled(true);
        ui->saveAsButton->setEnabled(true);
    }
}

void ParamDialog::on_saveButton_clicked()
{
    if(param != NULL && isChanged) {
        QFile file(SystemBase::path + name + QString(".") + SystemBase::postfix);
        param->writeParam(SystemBase::reagentNum, file);
        isChanged = false;
    }
}

void ParamDialog::on_saveAsButton_clicked()
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
}

void ParamDialog::on_confirmButton_clicked()
{
    saveCheck();
    QFile file(SystemBase::path + QString("/") + SystemBase::postfix);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out << name << endl;
        file.close();
    }
    accept();
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
