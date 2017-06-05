#include "webcam.h"
#include <QTimer>
#include <QImage>
#include <QDebug>

using namespace cv;


Webcam::Webcam(QWidget *parent) : QLabel(parent)
{
    cpt_ = 0;
    mainDetected_ = false;
    perdu_ = false;
    continuiteDetection_ = 0;
    webcamSize_ = QSize(640,240);
    webCam_=new VideoCapture(0);
    rectMain_ = Rect((webcamSize_.width()-50)/2,(webcamSize_.height()-50)/2,50,50);
    lastX_ = (webcamSize_.width()-50)/2;
    lastY_ = (webcamSize_.height()-50)/2;
    angle_ = 45;
    puissance_ = 0;
    if(webCam_->isOpened()){
        qDebug()<<"width :" << QString::number(webCam_->get(CV_CAP_PROP_FRAME_WIDTH)) << " height: " << QString::number(webCam_->get(CV_CAP_PROP_FRAME_HEIGHT));
        webCam_->set(CV_CAP_PROP_FRAME_WIDTH,640);
        webCam_->set(CV_CAP_PROP_FRAME_HEIGHT,480);
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(reload()));
        timer->start(10);
        if (webCam_->read(image_)){
            flip(image_,image_,1);
            image_ = Mat(image_, Rect(0,0,640,240));
            imageFond_ = Mat(image_, rectMain_).clone();
        }
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
            image_ = Mat(image_, Rect(0,0,640,240));
            if(!mainDetected_ && !detectionEnCours_){
                detecterMain();
            }
            else if(!mainDetected_ && detectionEnCours_){
                    if(cpt_ < 50){
                        if(cpt_ == 0){
                            lastX_ = 25;
                            lastY_ = 25;
                        }
                        cpt_ ++;
                        Mat resultImage;    // to store the matchTemplate result
                        resultImage.create( image_.cols-imageMain_.cols+1, image_.rows-imageMain_.rows+1, CV_32FC1 );

                        Mat zoneDetect = Mat(image_ , Rect(((webcamSize_.width()-50)/2) -25, ((webcamSize_.height()-50)/2) -25, 100, 100)).clone(); // detection autour du carré

                        matchTemplate( zoneDetect, imageMain_, resultImage, TM_CCORR_NORMED );
                        threshold(resultImage, resultImage, 0.1, 1., CV_THRESH_TOZERO);

                        // Localize the best match with minMaxLoc
                        double minVal; double maxVal; Point minLoc; Point maxLoc;
                        minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
                        //qDebug() << abs(maxLoc.x - lastX_);
                        if(abs(maxLoc.x -lastX_ ) < 20){
                            if(maxLoc.y - lastY_ < 50 && maxLoc.y - lastY_ > 4){

                                if (continuiteDetection_ > 2){
                                     detectionEnCours_ = false;
                                     mainDetected_ = true;
                                     matchTemplate( image_, imageMain_, resultImage, TM_CCORR_NORMED );
                                     threshold(resultImage, resultImage, 0.1, 1., CV_THRESH_TOZERO);

                                     // Localize the best match with minMaxLoc
                                     double minVal; double maxVal; Point minLoc; Point maxLoc;
                                     minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

                                     lastX_ = maxLoc.x;
                                     lastY_ = maxLoc.y;
                                     return;
                                }
                                else{
                                    continuiteDetection_ ++;
                                    //qDebug() << continuiteDetection_;
                                }

                            }else{
                                //qDebug() << "stop";
                                continuiteDetection_ = 0;
                            }

                        }
                    }else{
                        //qDebug() << "echec detection";
                        cpt_ = 0;
                        detectionEnCours_ = false;
                        lastX_ = (webcamSize_.width()-50)/2;
                        lastY_ = (webcamSize_.height()-50)/2;

                    }

                    rectangle(image_,rectMain_ ,Scalar( 0, 255, 0),2);
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

    Mat resultImage;    // to store the matchTemplate result
    resultImage.create( image_.cols-imageMain_.cols+1, image_.rows-imageMain_.rows+1, CV_32FC1 );
    Mat zoneDetect = Mat(image_ , Rect(((webcamSize_.width()-50)/2) -25, ((webcamSize_.height()-50)/2) -25, 100, 100)).clone(); // detection autour du carré

    matchTemplate( zoneDetect, imageFond_, resultImage, TM_CCORR_NORMED );
    threshold(resultImage, resultImage, 0.1, 1., CV_THRESH_TOZERO);

    // Localize the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    // Save the location fo the matched rect
    //qDebug() <<minVal<< " in " << abs(minLoc.x -25) << ":"<<abs(minLoc.y -25);
    if(minVal < 0.95 && abs(minLoc.x -25) < 30 && abs(minLoc.y -25) < 30){ // verif par rapport origine carré
        //qDebug() <<" detection demarré";

        if (continuiteDetection_ < 10) {
            continuiteDetection_ ++;
        }else{
            continuiteDetection_ = 0;
            imageMain_ = Mat(image_, rectMain_).clone();
            detectionEnCours_ = true;
        }


    }else{
        continuiteDetection_ = 0;
    }

    rectangle(image_,rectMain_ ,Scalar( 0, 255, 0),2);
}

void Webcam::suivreMain(){
    // Create the matchTemplate image result
    Mat resultImage;    // to store the matchTemplate result
    resultImage.create( image_.cols-imageMain_.cols+1, image_.rows-imageMain_.rows+1, CV_32FC1 );
    Rect resultRect;    // to store the location of the matched rect

    // TODO : Tentative reduire zone recherche proximité dernière zone
   /* if(!perdu_){
        // Do the Matching between the frame and the templateImage
        int coordX, coordY, tailleX, tailleY;
        qDebug() << lastX_ << lastY_;
        if(lastX_>25 && lastY_>25){
            coordX = lastX_-25;
            coordY = lastY_-25;
        }else if(lastX_>25){
            coordX = lastX_-25;
            coordY = 0;
        }else if(lastY_>25){
            coordX = 0;
            coordY = lastY_-25;
        }else{
            coordX = 0;
            coordY = 0;
        }

        if(coordX + 100 < webcamSize_.width() && coordY + 100 < webcamSize_.height()){
            tailleX = 100;
            tailleY = 100;
        }else if(coordX + 100 < webcamSize_.width()){
            tailleX = 100;
            tailleY = webcamSize_.height()-coordY;
        }
        else if(coordY + 100 < webcamSize_.height()){
            tailleX = webcamSize_.width() - coordX;
            tailleY = 100;
        }else{
            tailleX = webcamSize_.width() - coordX;
            tailleY = webcamSize_.height()-coordY;
        }
        Rect rectRecherche(coordX, coordY, tailleX, tailleY);
        Mat zoneRecherche = Mat(image_, rectRecherche).clone();
        matchTemplate( zoneRecherche, imageMain_, resultImage, TM_CCORR_NORMED );
    }
    else{
        matchTemplate( image_, imageMain_, resultImage, TM_CCORR_NORMED );
    }*/
    matchTemplate( image_, imageMain_, resultImage, TM_CCORR_NORMED );
    threshold(resultImage, resultImage, 0.1, 1., CV_THRESH_TOZERO);
    // Localize the best match with minMaxLoc
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    // Save the location fo the matched rect
    if(abs(maxLoc.x-lastX_) > 150 || abs(maxLoc.y-lastY_) > 150){
        //qDebug() <<" Tracking Perdu";
        perdu_ = true;
        return;
    }
    if(abs(maxLoc.x - lastX_) > 3 && maxLoc.y - lastY_ < 7){
        //qDebug() <<" Move X";
        angle_ += maxLoc.x - lastX_;
        if(angle_ < -90){
            angle_ = -90;
        }else if (angle_ > 90){
            angle_ = 90;
        }
        trebuchet_->setrot(angle_, trebuchet_->getu(), trebuchet_->gete());
        emit changementOpenGl();
    }
    if(abs(maxLoc.y - lastY_) > 3 && abs(maxLoc.x - lastX_) < 7 && maxLoc.y - lastY_ < 12){
        //qDebug() <<" Move Y";
        puissance_ += (maxLoc.y - lastY_ )*0.7;
        if(puissance_ < -5){
            puissance_ = -5;
        }else if( puissance_ > 20){
            puissance_ = 20;
        }
        trebuchet_->setrot(trebuchet_->getc(), puissance_, trebuchet_->gete());
        emit changementOpenGl();
    }
    if(maxLoc.y - lastY_ >= 17){
        //qDebug() << "FEU !!!!";
        mainDetected_ = false;
        lastX_ = (webcamSize_.width()-50)/2;
        lastY_ = (webcamSize_.height()-50)/2;
        return;
    }
    perdu_ = false;
    lastX_ = maxLoc.x;
    lastY_ = maxLoc.y;
    resultRect=Rect(maxLoc.x,maxLoc.y,50, 50);




    rectangle(image_,resultRect,Scalar( 0, 255, 0),2);




}
