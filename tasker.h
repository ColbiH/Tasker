#ifndef TASKER_H
#define TASKER_H

#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QMainWindow>
#include <QStandardItemModel>
#include "usermodel.h"
#include "task.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Tasker; }
QT_END_NAMESPACE

class Tasker : public QMainWindow
{
    Q_OBJECT

public:
    Tasker(QWidget *parent = nullptr);
    ~Tasker();

private:
    void initModel();
    void updateModel(vector<task> tasks);
    task to_task(QList<QString> q_task);
    QList<QString> from_task(task _task);
    QList<QString> modelToItems(UserModel* model);
    QList<QString> modelToCourses(UserModel *model);
    void setList();
    void updateColors();
    void loadColor();
    void storeColor();

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_actionImport_ics_File_triggered();

    void on_addTask_clicked();

    void on_deleteTask_clicked();

    void on_submitChanges_clicked();

    void on_actionSave_Tasks_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionExit_Without_Saving_triggered();

    void on_actionExit_And_Save_triggered();

    void closeEvent (QCloseEvent *event);

    //void on_listView_clicked(const QModelIndex &index);

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Tasker *ui;
    bool madeChanges;
    bool forceExit;
    QMap<int, QColor> colorMapIn;
    QMap<QString, int> colorCoordination;
    UserModel* model;
    task::task_colors colors = task::task_colors(QString("Resources/colors.txt").toStdString());

};
#endif // TASKER_H
