#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "EmulatorPDP11.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    EmulatorPDP11 *emul_;

    void UpdateFrames();

};

#endif // MAINWINDOW_H
