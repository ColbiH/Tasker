#include "tasker.h"
#include "ui_tasker.h"

#include "task.h"
#include "task_sorting.h"
#include "FileIO.h"
#include <iostream>


#include <QTableView>
#include <usermodel.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>


int currentTask = 0;

#include <QPixmap>


Tasker::Tasker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasker)
{
    ui->setupUi(this);


    initModel();

    //connect(ui->pButton, &QPushButton::clicked, this, &Tasker::on_pushButton_clicked);


    /*This is for the tasker logo, not sure how to write the file path so that
     * it's not a local path*/

    QPixmap pix("Resources/Tasker_logo.png");
    ui->label_logo->setScaledContents(true);
    ui->label_logo->setPixmap(pix);

}

Tasker::~Tasker()
{
    delete ui;
}

task Tasker::to_task(QList<QString> q_task){
    task holder;
    holder.set_name(q_task[0].toStdString());
    holder.set_description(q_task[1].toStdString());
    holder.set_duedate(q_task[2].toStdString());
    holder.set_course(q_task[3].toStdString());
    holder.set_weight(stoi(q_task[4].toStdString()));
    holder.set_diff(stoi(q_task[5].toStdString()));
    holder.set_complete(stoi(q_task[6].toStdString()));
    return holder;
}


QList<QString> Tasker::from_task(task _task){
    QList<QString> holder;

    holder.append(QString::fromStdString(_task.get_name()));
    holder.append(QString::fromStdString(_task.get_description()));
    holder.append(QString::fromStdString(_task.get_duedate()));
    holder.append(QString::fromStdString(_task.get_course()));
    holder.append(QString::fromStdString(to_string(_task.get_weight())));
    holder.append(QString::fromStdString(to_string(_task.get_diff())));
    holder.append(QString::fromStdString(to_string(_task.get_complete())));
    return holder;
}

void Tasker::initModel()
{
    model = new UserModel(7);


    vector<task> tasks = Open_File();
    for (int i = 0; i < tasks.size(); i++) {

            QList<QString> test = from_task(tasks.at(i));

            model->append(test);
            model->reset();
    }

    //For List View!!

    ui->listView->setModel(model);
    ui->comboBox->setModel(model);

    forceExit = false;
    madeChanges = false;
}

void Tasker::closeEvent (QCloseEvent *event)
{
    if (!forceExit && madeChanges){
        QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Tasker",
                                                                   tr("Do you want to save before exiting?\n"),
                                                                   QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                   QMessageBox::Yes);
        if (resBtn == QMessageBox::Cancel) {
            event->ignore();
        } else if(resBtn == QMessageBox::No){
            event->accept();
        } else if (resBtn == QMessageBox::Yes){
            vector<task> outTasks;
            for (int i = 0; i < model->rowCount(); i++){
                outTasks.push_back(to_task(model->getLine(i)));
            }

            Write_File(outTasks);
            event->accept();
        }
    }
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

void Tasker::on_actionImport_ics_File_triggered()
{
    //ICS File
    QString filter = "Calender File (*.ics)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open a Calender File", QDir::homePath(), filter);
    vector<task> tasks = load_ics(file_name.toStdString());
    for(unsigned int i=0 ; i<tasks.size() ; i++){
        model->append(from_task(tasks[i]));
        model->reset();
    }
    madeChanges = true;
}


void Tasker::on_addTask_clicked()
{
    QString name = ui->newName->text();
    QString desc = ui->newDesc->toPlainText();
    QString duedate = ui->newDueDate->text();
    QString course = ui->newCourse->text();
    QString weight = ui->newWeight->text();
    QString diff = ui->newDifficulty->text();
    string weightTemp = weight.toStdString();
    bool weightValid = all_ints(weightTemp);
    string diffTemp = diff.toStdString();
    bool diffValid = all_ints(diffTemp);
    string dateTemp = duedate.toStdString();

    if(!validDate(dateTemp)){
        QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText("Invalid Input");
            msgBox->setWindowModality(Qt::NonModal);
            msgBox->setInformativeText("The due date field must have the format: mm/dd/yyyy");
            msgBox->exec();
    }else if (!weightValid && !diffValid){
        QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText("Invalid Input");
            msgBox->setWindowModality(Qt::NonModal);
            msgBox->setInformativeText("The difficulty and weight fields must contain a positive integer");
            msgBox->exec();
    }
    else if (!weightValid){
        QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText("Invalid Input");
            msgBox->setWindowModality(Qt::NonModal);
            msgBox->setInformativeText("The weight field must contain a positive integer");
            msgBox->exec();
    }
    else if (!diffValid){
        QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText("Invalid Input");
            msgBox->setWindowModality(Qt::NonModal);
            msgBox->setInformativeText("The difficulty field must contain a positive integer");
            msgBox->exec();
    }
    else{
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
        madeChanges = true;
    }

}


void Tasker::on_deleteTask_clicked()
{
    if (model->rowCount() != 0){
        model->deleteList(currentTask);
        model->reset();
        madeChanges = true;
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
        //input
        QString name = ui->showName->text();
        QString desc = ui->showDesc->toPlainText();
        QString duedate = ui->showDueDate->text();
        QString course = ui->showCourseName->text();
        QString weight = ui->showWeight->text();
        QString diff = ui->showDifficulty->text();
        bool checked = ui->checkBox->isChecked();
        string weightTemp = weight.toStdString();
        bool weightValid = all_ints(weightTemp);
        string diffTemp = diff.toStdString();
        bool diffValid = all_ints(diffTemp);
        string dateTemp = duedate.toStdString();

        if(!validDate(dateTemp)){
            QMessageBox *msgBox = new QMessageBox(this);
                msgBox->setText("Invalid Input");
                msgBox->setWindowModality(Qt::NonModal);
                msgBox->setInformativeText("The due date field must have the format: mm/dd/yyyy");
                msgBox->exec();
        }else if (!weightValid && !diffValid){
            QMessageBox *msgBox = new QMessageBox(this);
                msgBox->setText("Invalid Input");
                msgBox->setWindowModality(Qt::NonModal);
                msgBox->setInformativeText("The difficulty and weight fields must contain a positive integer");
                msgBox->exec();
        }
        else if (!weightValid){
            QMessageBox *msgBox = new QMessageBox(this);
                msgBox->setText("Invalid Input");
                msgBox->setWindowModality(Qt::NonModal);
                msgBox->setInformativeText("The weight field must contain a positive integer");
                msgBox->exec();
        }
        else if (!diffValid){
            QMessageBox *msgBox = new QMessageBox(this);
                msgBox->setText("Invalid Input");
                msgBox->setWindowModality(Qt::NonModal);
                msgBox->setInformativeText("The difficulty field must contain a positive integer");
                msgBox->exec();
        }
        else{
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
            addTask.append(QString::fromStdString(to_string((int)checked)));
            model->insert(addTask, currentTask + tempcurr);
            model->reset();
            ui->comboBox->setCurrentIndex(currentTask + tempcurr);
            madeChanges = true;
        }
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


void Tasker::on_actionSave_Tasks_triggered()
{
    vector<task> outTasks;
    for (int i = 0; i < model->rowCount(); i++){
        outTasks.push_back(to_task(model->getLine(i)));
    }

    Write_File(outTasks);
    madeChanges = false;
}

void Tasker::updateModel(vector<task> tasks){
    delete[] model;
    model = new UserModel(7);
    for (int i = 0; i < tasks.size(); i++) {
        QList<QString> test = from_task(tasks.at(i));

        model->append(test);
        model->reset();
    }

    //For List View!!
    ui->listView->setModel(model);
    ui->comboBox->setModel(model);
}

void Tasker::on_pushButton_clicked()
{
    // Sort tasks based on due date.
    vector<task> tasks;
    for (int i = 0; i < model->rowCount(); i++){
        tasks.push_back(to_task(model->getLine(i)));
    }
    tasks = task_sort(tasks, attributes::date);
    updateModel(tasks);
}

void Tasker::on_pushButton_2_clicked()
{
    // Sort by Course
    vector<task> tasks;
    for (int i = 0; i < model->rowCount(); i++){
        tasks.push_back(to_task(model->getLine(i)));
    }
    tasks = task_sort(tasks, attributes::course);
    updateModel(tasks);
}

void Tasker::on_pushButton_3_clicked()
{
    // Sort by Weight
    vector<task> tasks;
    for (int i = 0; i < model->rowCount(); i++){
        tasks.push_back(to_task(model->getLine(i)));
    }
    tasks = task_sort(tasks, attributes::weight);
    updateModel(tasks);
}


void Tasker::on_pushButton_4_clicked()
{
    // Sort by Difficulty
    vector<task> tasks;
    for (int i = 0; i < model->rowCount(); i++){
        tasks.push_back(to_task(model->getLine(i)));
    }
    tasks = task_sort(tasks, attributes::diff);
    updateModel(tasks);
}


void Tasker::on_actionExit_Without_Saving_triggered()
{
    forceExit = true;
    QApplication::quit();
}


void Tasker::on_actionExit_And_Save_triggered()
{
    vector<task> outTasks;
    for (int i = 0; i < model->rowCount(); i++){
        outTasks.push_back(to_task(model->getLine(i)));
    }

    Write_File(outTasks);
    forceExit = true;
    QApplication::quit();
}


void Tasker::on_listView_clicked(const QModelIndex &index)
{
    currentTask = index.row();
    ui->showName->setText(model->getData(index.row(), 0));
    ui->showDesc->setText(model->getData(index.row(), 1));
    ui->showDueDate->setText(model->getData(index.row(), 2));
    ui->showCourseName->setText(model->getData(index.row(), 3));
    ui->showWeight->setText(model->getData(index.row(), 4));
    ui->showDifficulty->setText(model->getData(index.row(), 5));
    bool checked = QVariant(model->getData(index.row(), 6)).toBool();
    ui->checkBox->setChecked(checked);
}
