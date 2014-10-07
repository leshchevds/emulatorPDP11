#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    if (parent == 0) {
        emul_ = new EmulatorPDP11();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    ui->label->setText("ohoho");
    QPixmap mypix(512,256);
    mypix.fill(Qt::blue);
    ui->label->setPixmap(mypix);

}

void MainWindow::on_pushButton_2_clicked() {
    UpdateFrames();
}

void MainWindow::UpdateFrames() {
    QImage::Format format = QImage::Format_Mono;
    QImage image(512, 256, format);

    const char* frame = emul_->videomem();

    while (1) {
        for (int i = 0; i < 512; ++i) {
            for (int j = 0; j < 256; ++j) {
                image.setPixel(i,j,frame[(i * 256 + j) / 8] & (1 << (j % 8)));
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(image));
        QThread::msleep(100);
    }
}
