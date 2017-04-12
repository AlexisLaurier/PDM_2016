#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"
#include <QTimer>

using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    webCam_=new VideoCapture(0);
    if(webCam_->isOpened()){
        ui->webcam->setMaximumHeight(200);

    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reload()));
    timer->start(10);

}

void MainWindow::reload(){
    if (webCam_->isOpened()) {
        Mat image;
        if (webCam_->read(image)) {   // Capture a frame
            // Flip to get a mirror effect
            flip(image,image,1);
            // Invert Blue and Red color channels
            cvtColor(image,image,CV_BGR2RGB);
            // Convert to Qt image
            QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
            // Display on label
            ui->webcam->setPixmap(QPixmap::fromImage(img));


        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
