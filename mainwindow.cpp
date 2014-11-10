#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QPixmap>
#include <QFuture>
#include <QtConcurrent>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    if (parent == 0) {
        emul_ = new EmulatorPDP11();
        future_ =  QtConcurrent::run(this, &MainWindow::UpdateFrames);
    }

    qRegisterMetaType<QVector<int> >("QVector<int>");
    OpListModel_ = new QStringListModel();
    ui->OpsListView->setModel(OpListModel_);
    run_lock_ = false;
}

MainWindow::~MainWindow() {
    isWorking_ = 0;
    runApproved_.store(false);
    bool expected = false;
    while (!run_lock_.compare_exchange_strong(expected, true)) {
        expected = false;
    }

    if (emul_) {
       future_.waitForFinished();
       delete emul_;
    }
    delete ui;
}

void MainWindow::PushOperation(std::string str) {
    OpListModel_->insertRow(0);
    QModelIndex index = OpListModel_->index(0);
    const int MAX_ROWS = 10;
    if (OpListModel_->rowCount() == MAX_ROWS) {
        OpListModel_->removeRow(MAX_ROWS - 1);
    }
    OpListModel_->setData(index, str.c_str());
}

void MainWindow::OpListReset() {
    OpListModel_->removeRows(0, OpListModel_->rowCount());
}


void MainWindow::Step() {
    bool expected = false;
    if (run_lock_.compare_exchange_strong(expected, true)) {
        QtConcurrent::run(this, &MainWindow::StepWorker);
    }
}

void MainWindow::StepWorker() {
    PushOperation(emul_->step_and_list());
    run_lock_.store(false);
}

void MainWindow::Run() {
    bool expected = false;
    if (run_lock_.compare_exchange_strong(expected, true)) {
        runApproved_.store(true);
        QtConcurrent::run(this, &MainWindow::RunWorker);
    }
}

void MainWindow::Stop() {
    runApproved_.store(false);
}

void MainWindow::RunWorker() {
    while (runApproved_.load()) {
        emul_->step_and_list();
    }
    run_lock_.store(false);
}


class Thread : public QThread
{
public:
    static void msleep(int ms)
    {
        QThread::msleep(ms);
    }
};

void MainWindow::UpdateFrames() {
    QImage::Format format = QImage::Format_Mono;
    QImage image(512, 256, format);

    char* const frame = emul_->videomem();

    while (true) {
        if (!isWorking_) {
            break;
        }
        for (int i = 0; i < 256; ++i) {
            for (int j = 0; j < 512; ++j) {
                image.setPixel(j, 255 - i,
                               !(bool)(frame[(i*512 + j) / 8] & (1 << (7 - j % 8))));
            }
        }
        ui->ScreenLabel->setPixmap(QPixmap::fromImage(image));

        ui->R0_LCD->display(emul_->reg(0));
        ui->R1_LCD->display(emul_->reg(1));
        ui->R2_LCD->display(emul_->reg(2));
        ui->R3_LCD->display(emul_->reg(3));
        ui->R4_LCD->display(emul_->reg(4));
        ui->R5_LCD->display(emul_->reg(5));
        ui->R6_LCD->display(emul_->reg(6));
        ui->R7_LCD->display(emul_->reg(7));
        ui->NFlagLCD->display(emul_->NFlag());
        ui->ZFlagLCD->display(emul_->ZFlag());
        ui->VFlagLCD->display(emul_->VFlag());
        ui->CFlagLCD->display(emul_->CFlag());

        Thread::msleep(40);
    }
}

void MainWindow::on_ResetButton_clicked() {
    Stop();
    emul_->Reset();
    OpListReset();
}

void MainWindow::on_StepButton_clicked() {
    Step();
}

void MainWindow::on_GoButton_clicked() {
    Run();
}

void MainWindow::on_StopButton_clicked() {
    Stop();
}
