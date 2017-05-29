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

signals:

public slots:
    void reload();
private:

    cv::VideoCapture * webCam_;
};

#endif // WEBCAM_H
