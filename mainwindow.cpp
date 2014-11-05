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

    OpListModel_ = new QStringListModel(this);
    ui->listView->setModel(OpListModel_);
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
                image.setPixel(j, 255 - i, (bool)(frame[(i*512 + j) / 8] & (1 << (j % 8))));
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(image));
        Thread::msleep(1000);

    }
}


void MainWindow::PushOperation(QString str) {
    OpListModel_->insertRow(0);
    QModelIndex index = OpListModel_->index(0);
    const int MAX_ROWS = 10;
    if (OpListModel_->rowCount() == MAX_ROWS) {
        OpListModel_->removeRow(MAX_ROWS - 1);
    }
    OpListModel_->setData(index, str);
}

void MainWindow::on_pushButton_clicked() {
    ui->label->setText("ohoho");
    QPixmap mypix(512,256);
    mypix.fill(Qt::blue);
    ui->label->setPixmap(mypix);
}

void MainWindow::on_pushButton_2_clicked() {
    PushOperation("aaah");
}

void MainWindow::on_pushButton_3_clicked() {

}

void MainWindow::on_pushButton_4_clicked() {
    PushOperation("ooh");
}
