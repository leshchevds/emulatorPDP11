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
}

MainWindow::~MainWindow() {
    isWorking_ = 0;
    if (emul_) {
       future_.waitForFinished();
       delete emul_;
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    ui->label->setText("ohoho");
    QPixmap mypix(512,256);
    mypix.fill(Qt::blue);
    ui->label->setPixmap(mypix);

}

void MainWindow::on_pushButton_2_clicked() {

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

    const char* frame = emul_->videomem();

    while (1) {
        if (!isWorking_) {
            break;
        }
        for (int i = 0; i < 256; ++i) {
            for (int j = 0; j < 512; ++j) {
                image.setPixel(j, i, (frame[(i*512 + j) / 8] & (1 << (j % 8))) == 1);
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(image));
        Thread::msleep(100);

    }
}
