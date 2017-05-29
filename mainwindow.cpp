#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"


using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    webcam = new Webcam();

}



MainWindow::~MainWindow()
{
    delete ui;
}
