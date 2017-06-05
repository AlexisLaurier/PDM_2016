#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/opencv.hpp"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>


using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->openGLWidget->settrebuchet(&trebuchet);
    ui->openGLWidget->setcamera(&camera);
    ui->openGLWidget->setboule(&boule);
    ui->openGLWidget->setcible(&cible);
    ui->openGLWidget->setbouleenlair(&bouleenlair);
    ui->webcam->setTrebuchet(&trebuchet);
    ui->webcam->setTir(&tir_);

    tir_.setboule(&boule);
    tir_.setbouleenlair(&bouleenlair);
    tir_.setcible(&cible);
    tir_.settrebuchet(&trebuchet);


    tirencours=false;
    horlogeS_ = 0;
    horlogeM_ = 0;


    resetaffichage();

    timer_ = new QTimer(this);
    connect(ui->webcam, SIGNAL(changementOpenGl()), ui->openGLWidget, SLOT(updateGL()));
    connect(timer_, SIGNAL(timeout()), this, SLOT(incrementHorloge()));
    timer_->start(1000);


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
void MainWindow::resetaffichage()
{
    //initialisation du trébuchet
    trebuchet.setsize(0.02);
    trebuchet.setpos(0,-5,0);
    trebuchet.setrot(45,0,-20);
    trebuchet.setdisplayed(true);

    //initialisation de la boule
    boule.setsize(0.2);
    boule.setpos(0,0.1,-4);
    boule.setdisplayed(true);

    //initialisation de la boule en l'air
    bouleenlair.setdisplayed(false);

    //initialisation de la cible
    cible.setdisplayed(true);
    cible.setsize(0.15);
    cible.setpos(0,3,1);
    cible.setrot(60,0,0);

    //initialisation de la camera
    camera.setdisplayed(true);
    camera.setpos (0,-0.03,-0.27);
    camera.setrot(275,0,350);

    //position de la bouboule 0 -2.15 0.35
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    camera.setpos(double(position)/100,camera.gety(),camera.getz());
    ui->openGLWidget->updateGL();
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    camera.setpos(camera.getx(),double(position)/100,camera.getz());
    ui->openGLWidget->updateGL();
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    camera.setpos(camera.getx(),camera.gety(),double(position)/100);
    ui->openGLWidget->updateGL();
}

void MainWindow::on_horizontalSlider_4_sliderMoved(int position)
{
    camera.setrot(double(position),camera.getu(),camera.gete());
    ui->openGLWidget->updateGL();
}

void MainWindow::on_horizontalSlider_5_sliderMoved(int position)
{
    camera.setrot(camera.getc(),double(position),camera.gete());
    ui->openGLWidget->updateGL();
}

void MainWindow::on_horizontalSlider_6_sliderMoved(int position)
{
    camera.setrot(camera.getc(),camera.getu(),double(position));
    ui->openGLWidget->updateGL();
}

void MainWindow::incrementHorloge(){
    horlogeS_ += 1;
    if(horlogeS_ >= 60){
        horlogeS_ = 0;
        horlogeM_ += 1;
    }
    ui->timerLabel->setText(QString::number(horlogeM_) + "min " + QString::number(horlogeS_)+"s");
}
