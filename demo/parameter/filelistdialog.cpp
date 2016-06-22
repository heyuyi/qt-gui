#include "filelistdialog.h"
#include "ui_filelistdialog.h"

#include <QDir>
#include <QMessageBox>

FileListDialog::FileListDialog(QWidget *parent,
        const QString &p, const QString &f) :
    QDialog(parent),
    ui(new Ui::FileListDialog),
    dir(p), postfix(f)
{
    ui->setupUi(this);
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    QDir dir(this->dir);
    dir.setFilter(QDir::Files);
    dir.setNameFilters(QStringList("*" + postfix));
    QFileInfoList list = dir.entryInfoList();
    for(int i = 0; i < list.size(); ++i) {
        QString str = list.at(i).fileName();
        int n = str.lastIndexOf('.');
        ui->listWidget->addItem(str.left(n));
    }
}

FileListDialog::~FileListDialog()
{
    delete ui;
}

QString FileListDialog::selectedFile(void)
{
    return ui->listWidget->selectedItems().at(0)->text();
}

void FileListDialog::on_deleteButton_clicked()
{
    QListWidgetItem *item = ui->listWidget->selectedItems().at(0);
//    QMessageBox::information(this, "提示", item->text(), QMessageBox::Yes);
    QFile::remove(dir + item->text() + postfix);
    ui->listWidget->removeItemWidget(item);
    delete item;
}

void FileListDialog::on_confirmButton_clicked()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    if(list.isEmpty())
        QMessageBox::warning(this, QObject::tr("提示"), QObject::tr("还没有选择打开的文件!"), QMessageBox::Yes);
    else
        accept();
}
