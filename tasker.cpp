#include "tasker.h"
#include "ui_tasker.h"

#include "task.h"
#include "FileIO.h"


#include <QTableView>
#include <usermodel.h>




//#include <QPixmap>


Tasker::Tasker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasker)
{
    ui->setupUi(this);


    initModel();

    connect(ui->pButton, &QPushButton::clicked, this, &Tasker::on_pushButton_clicked);


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


void Tasker::on_pushButton_2_clicked()
{
    //Submit Changes to task
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

