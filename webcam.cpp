#include "webcam.h"
#include <QTimer>
#include <QImage>
#include <QDebug>

using namespace cv;


Webcam::Webcam(QWidget *parent) : QLabel(parent)
{
    mainDetected_ = false;
    webcamSize_ = QSize(320,240);
    webCam_=new VideoCapture(0);
    rectMain_ = Rect((webcamSize_.width()-50)/2,(webcamSize_.height()-50)/2,50,50);
    if(webCam_->isOpened()){
        qDebug()<<"width :" << QString::number(webCam_->get(CV_CAP_PROP_FRAME_WIDTH)) << " height: " << QString::number(webCam_->get(CV_CAP_PROP_FRAME_HEIGHT));
        webCam_->set(CV_CAP_PROP_FRAME_WIDTH,webcamSize_.width());
        webCam_->set(CV_CAP_PROP_FRAME_HEIGHT,webcamSize_.height());
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(reload()));
        timer->start(10);
    }
    setMinimumSize(webcamSize_);



}

Webcam::~Webcam(){
    delete webCam_;
}

void Webcam::reload(){
    if (webCam_->isOpened()) {

        if (webCam_->read(image_)) { // Capture a frame

            // Flip to get a mirror effect
            flip(image_,image_,1);

            if(!mainDetected_){
                detecterMain();
            }else{
                suivreMain();
            }
            // Invert Blue and Red color channels
            cvtColor(image_,image_,CV_BGR2RGB);

            QImage img = QImage((const unsigned char*)(image_.data),image_.cols,image_.rows,QImage::Format_RGB888);
            // Display on label
            QPixmap pixmap = QPixmap::fromImage(img);
            setPixmap(pixmap);




        }
    }
}

void Webcam::detecterMain()
{


    rectangle(image_,rectMain_,Scalar( 0, 255, 0),2);

}

void Webcam::suivreMain(){
    // Create the matchTemplate image result
    Mat resultImage;    // to store the matchTemplate result
    resultImage.create( image_.cols-imageMain_.cols+1, image_.rows-imageMain_.rows+1, CV_32FC1 );
    Rect resultRect;    // to store the location of the matched rect

    // Do the Matching between the frame and the templateImage
    int coordX, coordY;
    if(lastX_>100 && lastY_>100){
        coordX = lastX_-100;
        coordY = lastY_-100;
    }else if(lastX_>100){
        coordX = lastX_-100;
        coordY = 0;
    }else if(lastY_>100){
        coordX = 0;
        coordY = lastY_-100;
    }else{
        coordX = 0;
        coordY = 0;
    }
    Rect rectRecherche(coordX, coordY, 100, 100);
    Mat zoneRecherche = Mat(image_, rectRecherche).clone();
     matchTemplate( zoneRecherche, imageMain_, resultImage, TM_CCORR_NORMED );

    // Localize the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    // Save the location fo the matched rect
    resultRect=Rect(maxLoc.x,maxLoc.y,50, 50);




    rectangle(image_,resultRect,Scalar( 0, 255, 0),2);




}
