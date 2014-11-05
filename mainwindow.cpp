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


    ui->OpsListView->setModel(emul_->OpListModel_);
}

MainWindow::~MainWindow() {
    isWorking_ = 0;
    if (emul_) {
       future_.waitForFinished();
       delete emul_;
    }
    delete ui;
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

        Thread::msleep(100);
    }
}

void MainWindow::on_ResetButton_clicked() {
    emul_->Reset();
}

void MainWindow::on_StepButton_clicked() {
    emul_->Step();
}

void MainWindow::on_GoButton_clicked() {
    emul_->Run();
}

void MainWindow::on_StopButton_clicked() {
    emul_->Stop();
}
