#include "tasker.h"
#include "ui_tasker.h"

#include "task.h"
#include "FileIO.h"


#include <QTableView>
#include <usermodel.h>


int currentTask = 0;

//#include <QPixmap>


Tasker::Tasker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasker)
{
    ui->setupUi(this);


    initModel();

    //connect(ui->pButton, &QPushButton::clicked, this, &Tasker::on_pushButton_clicked);


    /*This is for the tasker logo, not sure how to write the file path so that
     * it's not a local path*/

    //QPixmap pix("C:/Users/jorda/OneDrive/Documents/GitHub/Tasker/Tasker_logo.png");
    //ui->label_logo->setPixmap(pix);

}

Tasker::~Tasker()
{
    delete ui;
}


void Tasker::initModel()
{
    model = new UserModel(7);


    vector<task> tasks = Open_File();
    for (int i = 0; i < tasks.size(); i++) {

        QString name = QString::fromStdString(tasks.at(i).get_name());
        QString desc = QString::fromStdString(tasks.at(i).get_description());
        QString duedate = QString::fromStdString(tasks.at(i).get_duedate());
        QString course = QString::fromStdString(tasks.at(i).get_course());
        QString weight = QString::fromStdString(to_string(tasks.at(i).get_weight()));
        QString diff = QString::fromStdString(to_string(tasks.at(i).get_diff()));
        QString complete = QString::fromStdString(to_string((int)tasks.at(i).get_complete()));

        QList<QString> test;
        test.append(name);
        test.append(desc);
        test.append(duedate);
        test.append(course);
        test.append(weight);
        test.append(diff);
        test.append(complete);

        model->append(test);
        model->reset();
    }

    //For List View!!

    ui->listView->setModel(model);
    ui->comboBox->setModel(model);
}

void Tasker::on_checkBox_stateChanged(int arg1)
{
    //Checkbox for marking a task as complete

}


void Tasker::on_pushButton_clicked()
{



}


void Tasker::on_comboBox_currentIndexChanged(int index)
{

    currentTask = index;
    ui->showName->setText(model->getData(index, 0));
    ui->showDesc->setText(model->getData(index, 1));
    ui->showDueDate->setText(model->getData(index, 2));
    ui->showCourseName->setText(model->getData(index, 3));
    ui->showWeight->setText(model->getData(index, 4));
    ui->showDifficulty->setText(model->getData(index, 5));
    bool checked = QVariant(model->getData(index, 6)).toBool();
    ui->checkBox->setChecked(checked);


    //Old Delete Task Button
}


void Tasker::on_pushButton_5_clicked()
{
    //Add new task
}


void Tasker::on_actionImport_ics_File_triggered()
{
    //ICS File
}


void Tasker::on_addTask_clicked()
{
    QString name = ui->newName->text();
    QString desc = ui->newDesc->toPlainText();
    QString duedate = ui->newDueDate->text();
    QString course = ui->newCourse->text();
    QString weight = ui->newWeight->text();
    QString diff = ui->newDifficulty->text();
    QList<QString> addTask;
    addTask.append(name);
    addTask.append(desc);
    addTask.append(duedate);
    addTask.append(course);
    addTask.append(weight);
    addTask.append(diff);
    addTask.append("0");
    model->append(addTask);
    model->reset();
}


void Tasker::on_deleteTask_clicked()
{
    if (model->rowCount() != 0){
        model->deleteList(currentTask);
        model->reset();
        if (model->rowCount() == 0){
            ui->showName->clear();
            ui->showDesc->clear();
            ui->showDueDate->clear();
            ui->showCourseName->clear();
            ui->showWeight->clear();
            ui->showDifficulty->clear();
            ui->checkBox->setChecked(false);
        }
    }

}


void Tasker::on_submitChanges_clicked()
{
    //Delete current task, then create a new one with current fields
    if (model->rowCount() != 0){
        QString name = ui->showName->text();
        QString desc = ui->showDesc->toPlainText();
        QString duedate = ui->showDueDate->text();
        QString course = ui->showCourseName->text();
        QString weight = ui->showWeight->text();
        QString diff = ui->showDifficulty->text();
        bool checked = ui->checkBox->isChecked();
        int tempcurr = currentTask;
        model->deleteList(currentTask);
        model->reset();

        QList<QString> addTask;
        addTask.append(name);
        addTask.append(desc);
        addTask.append(duedate);
        addTask.append(course);
        addTask.append(weight);
        addTask.append(diff);
        addTask.append(QVariant(checked).toString());
        model->insert(addTask, currentTask + tempcurr);
        model->reset();
        ui->comboBox->setCurrentIndex(currentTask + tempcurr);

    }
    else{
        ui->showName->clear();
        ui->showDesc->clear();
        ui->showDueDate->clear();
        ui->showCourseName->clear();
        ui->showWeight->clear();
        ui->showDifficulty->clear();
        ui->checkBox->setChecked(false);
    }
}

