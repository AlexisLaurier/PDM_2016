#ifndef WEBCAM_H
#define WEBCAM_H

#include <QWidget>
#include <QLabel>
#include "opencv2/opencv.hpp"


class Webcam : public QLabel
{
    Q_OBJECT
public:
    explicit Webcam(QWidget *parent = 0);
    ~Webcam();
    bool mainDetected() { return mainDetected_;}
    cv::Mat image() { return image_;}
    cv::Mat imageMain() { return imageMain_;}
    cv::Rect rectMain() { return rectMain_;}
    void setMainDetected(bool mainDetected) { mainDetected_ = mainDetected; }
    void setImageMain(cv::Mat imageMain) { imageMain_=imageMain; }
    void setLastX(int x){ lastX_=x;}
    void setLastY(int y){ lastY_=y;}
    void suivreMain();
    void detecterMain();

signals:

public slots:
    void reload();
private:
    cv::Mat image_;
    cv::Mat imageMain_;
    cv::Mat imageResultat_;
    cv::VideoCapture * webCam_;
    QSize webcamSize_;
    bool mainDetected_;
    bool perdu_;
    cv::Rect rectMain_;
    int lastX_;
    int lastY_;
    QTimer *timer;
    double angle_;
    double puissance_;
};

#endif // WEBCAM_H
