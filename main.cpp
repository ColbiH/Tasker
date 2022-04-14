#include "tasker.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "task.h"
#include "FileIO.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("Resources/Tasker_logo.png"));
    Tasker w;
    w.show();
    return a.exec();
}
