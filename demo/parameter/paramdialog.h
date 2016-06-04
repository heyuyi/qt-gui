#ifndef PARAMDIALOG_H
#define PARAMDIALOG_H

#include "base/basedialog.h"
#include "base/paramdata.h"
#include "numberdialog.h"

#include <QStandardItemModel>

namespace Ui {
class ParamDialog;
}

class ParamDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit ParamDialog(QWidget *parent = 0);
    ~ParamDialog();

private:
    void saveCheck(void);
    void displayUpdate(void);

private slots:
    void nDialogOutValueSLOT();

    void on_paramView_clicked(const QModelIndex &index);

    void on_newButton_clicked();

    void on_openButton_clicked();

    void on_saveButton_clicked();

    void on_saveAsButton_clicked();

    void on_confirmButton_clicked();

    void on_enableCheckBox_clicked();

    void on_pumpSpeedEdit_released();

    void on_delayEdit_released();

    void on_quantityEdit_released();

    void on_speedEdit_released();

    void on_delay1Edit_released();

    void on_pumpEdit_released();

    void on_delay2Edit_released();

private:
    Ui::ParamDialog *ui;
    NumberDialog *nDialog;
    ParamData *param;
    QStandardItemModel *treeModel;
    QString name;
    int treeItem;
    int editItem;
    bool isChanged;
};

#endif // PARAMDIALOG_H
