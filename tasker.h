#ifndef TASKER_H
#define TASKER_H

#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QMainWindow>
#include <QStandardItemModel>
#include "usermodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Tasker; }
QT_END_NAMESPACE

class Tasker : public QMainWindow
{
    Q_OBJECT

public:
    Tasker(QWidget *parent = nullptr);
    ~Tasker();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    void initModel();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_actionImport_ics_File_triggered();

    void on_addTask_clicked();

private:
    Ui::Tasker *ui;

    UserModel* model;

};
#endif // TASKER_H
