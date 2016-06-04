#ifndef FILELISTDIALOG_H
#define FILELISTDIALOG_H

#include <QDialog>

namespace Ui {
class FileListDialog;
}

class FileListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileListDialog(QWidget *parent, const QString &dir, const QString &postfix);
    ~FileListDialog();

    QString selectedFile(void);

private slots:

    void on_deleteButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::FileListDialog *ui;
    const QString dir;
    const QString postfix;
};

#endif // FILELISTDIALOG_H
