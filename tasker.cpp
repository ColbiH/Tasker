#include "tasker.h"
#include "ui_tasker.h"

Tasker::Tasker(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasker)
{
    ui->setupUi(this);
}

Tasker::~Tasker()
{
    delete ui;
}

