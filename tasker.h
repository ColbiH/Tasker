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

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Tasker *ui;
};
#endif // TASKER_H
