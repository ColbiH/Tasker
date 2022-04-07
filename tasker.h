#ifndef TASKER_H
#define TASKER_H

#include <QMainWindow>

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
    Ui::Tasker *ui;
};
#endif // TASKER_H
