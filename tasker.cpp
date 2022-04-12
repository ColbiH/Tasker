#include "tasker.h"
#include "ui_tasker.h"
//#include <QPixmap>

Tasker::Tasker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasker)
{
    ui->setupUi(this);
    /*This is for the tasker logo, not sure how to write the file path so that
     * it's not a local path*/

    //QPixmap pix("C:/Users/jorda/OneDrive/Documents/GitHub/Tasker/Tasker_logo.png");
    //ui->label_logo->setPixmap(pix);
}

Tasker::~Tasker()
{
    delete ui;
}


void Tasker::on_checkBox_stateChanged(int arg1)
{
    //Checkbox for marking a task as complete
}


void Tasker::on_pushButton_clicked()
{
    //Delete Task
}


void Tasker::on_pushButton_2_clicked()
{
    //Submit Changes to task
}


void Tasker::on_pushButton_5_clicked()
{
    //Add new task
}

