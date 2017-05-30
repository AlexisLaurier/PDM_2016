#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"
#include <QKeyEvent>
#include <QDebug>

using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}



MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent ( QKeyEvent * event ){
     if(!ui->webcam->mainDetected() && event->key() == Qt::Key_Escape){
        qDebug() << "Main Detectée";
        Mat hand = Mat(ui->webcam->image(), ui->webcam->rectMain()).clone();
        ui->webcam->setImageMain(hand);
        ui->webcam->setMainDetected(true);
        return;
    }
}
