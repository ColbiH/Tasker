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
    model = new UserModel(4);


    //For List View!!

     ui->comboBox->setModel(model);
}

void Tasker::on_checkBox_stateChanged(int arg1)
{
    //Checkbox for marking a task as complete

}


void Tasker::on_pushButton_clicked()
{
    QList<QString> test;
    test.append("Task Name");
    test.append("Desc");
    test.append("Date");
    test.append("Weight");

    model->append(test);
    model->reset();
}



void Tasker::on_comboBox_currentIndexChanged(int index)
{


    ui->textEdit->setText(model->getData(index, 1));
    ui->textEdit_2->setText(model->getData(index, 2));
    ui->textEdit_3->setText(model->getData(index, 3));

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

