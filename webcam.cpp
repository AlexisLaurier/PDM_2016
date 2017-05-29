#include "webcam.h"
#include <QTimer>
using namespace cv;


Webcam::Webcam(QWidget *parent) : QLabel(parent)
{
    webCam_=new VideoCapture(0);
    if(webCam_->isOpened()){
       this->setMaximumHeight(200);

    }
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(reload()));
    timer->start(10);
}

void Webcam::reload(){
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
            this->setPixmap(QPixmap::fromImage(img));


        }
    }
}
