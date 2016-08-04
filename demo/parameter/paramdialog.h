#ifndef PARAMDIALOG_H
#define PARAMDIALOG_H

#include "base/paramdata.h"
#include "numberdialog.h"

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class ParamDialog;
}

class ParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParamDialog(QWidget *parent = 0);
    ~ParamDialog();

private:
    void saveCheck(void);
    void displayUpdate(void);

private slots:
    void dateTimerSLOT(void);

    void nDialogOutValueSLOT();

    void on_paramView_clicked(const QModelIndex &index);

    void on_enableCheckBox_clicked();

    void on_pumpSpeedEdit_released();

    void on_delayEdit_released();

    void on_quantityEdit_released();

    void on_speedEdit_released();

    void on_delay1Edit_released();

    void on_pumpEdit_released();

    void on_delay2Edit_released();

    void on_newLabel_pressed();

    void on_newLabel_released();

    void on_openLabel_pressed();

    void on_openLabel_released();

    void on_saveLabel_pressed();

    void on_saveLabel_released();

    void on_saveAsLabel_pressed();

    void on_saveAsLabel_released();

    void on_confirmLabel_pressed();

    void on_confirmLabel_released();

    void on_cancelLabel_pressed();

    void on_cancelLabel_released();

private:
    Ui::ParamDialog *ui;
    NumberDialog *nDialog;
    ParamData *param;
    QStandardItemModel *treeModel;
    QString name;
    short treeItem;
    short editItem;
    bool isChanged;
};

#endif // PARAMDIALOG_H
