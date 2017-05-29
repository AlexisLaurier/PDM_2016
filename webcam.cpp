#include "webcam.h"
#include <QTimer>
#include <QImage>
using namespace cv;


Webcam::Webcam(QWidget *parent) : QLabel(parent)
{


    webCam_=new VideoCapture(0);
    if(webCam_->isOpened()){
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(reload()));
        connect(timer, SIGNAL(timeout()), this, SLOT(detectHand()));
        timer->start(10);
    }



}

Webcam::~Webcam(){
    delete webCam_;
}

void Webcam::reload(){
    if (webCam_->isOpened()) {

        if (webCam_->read(image_)) {   // Capture a frame
            //detectHand();
            // Flip to get a mirror effect
            flip(image_,image_,1);
            // Invert Blue and Red color channels
            cvtColor(image_,image_,CV_BGR2RGB);
            // Convert to Qt image
            QImage img= QImage((const unsigned char*)(image_.data),image_.cols,image_.rows,QImage::Format_RGB888);
            // Display on label
            setPixmap(QPixmap::fromImage(img));


        }
    }
}

void Webcam::detectHand()
{
    Rect rectRoi(500,300,100,100);
    Mat  imgRoi;
    Mat roi(image_, rectRoi);
    roi.copyTo(imgRoi);
    imshow("roi",imgRoi);
    waitKey(10);

    rectangle(image_,rectRoi,Scalar( 0, 255, 0),2,8,0);

}
