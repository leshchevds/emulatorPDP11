#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "EmulatorPDP11.h"

#include <QMainWindow>
#include <QFuture>
#include <QStringListModel>
#include <QtConcurrentRun>
#include <QThread>
#include <QMetaType> // without this line methods from threads emit errors
#include <atomic>

class EmulatorPDP11;

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
    void on_StepButton_clicked();

    void on_ResetButton_clicked();

    void on_GoButton_clicked();

    void on_StopButton_clicked();

private:
    Ui::MainWindow *ui;
    EmulatorPDP11 *emul_ = 0;
    QFuture<void> future_;
    bool isWorking_ = 1;
    QStringListModel *OpListModel_;

    std::atomic_bool run_lock_;

    bool runApproved_;

    void PushOperation(std::string str);
    void OpListReset();
    void UpdateFrames();
    void Step();
    void StepWorker();
    void Run();
    void Stop();
    void RunWorker();

};

#endif // MAINWINDOW_H
