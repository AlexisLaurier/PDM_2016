#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include "webcam.h"
#include "element.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *ev);
    Element * gettrebuchet() {return &trebuchet;}
    Element * getboule() {return &boule;}
    Element * getcible(){return &cible;}


public slots:

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

    void on_horizontalSlider_4_sliderMoved(int position);

    void on_horizontalSlider_5_sliderMoved(int position);

    void on_horizontalSlider_6_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    Element trebuchet;
    Element boule;
    Element cible;
    Element camera;
};

#endif // MAINWINDOW_H
