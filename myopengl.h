// myopengl.h

#ifndef MYOPENGL_H
#define MYOPENGL_H
#include "opencv2/opencv.hpp"
#include <QGLWidget>
#include <QOpenGLTexture>
#include "element.h"


class MyOpenGl : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyOpenGl(QWidget *parent = 0);
    ~MyOpenGl();
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

public slots:
    void settrebuchet(Element* elm) {trebuchet = elm;}
    void setboule(Element* elm){boule=elm;}
    void setbouleenlair(Element* elm){bouleenlair=elm;}
    void setcible(Element* elm){cible=elm;}
    void setcamera(Element* elm){camera=elm;}


private:

    int xRot;
    int yRot;
    int zRot;
    double xTrans;
    double yTrans;
    double zTrans;
    QOpenGLTexture *textures[6];
    QPoint lastPos;
    QWidget *parent_;
    Element *trebuchet;
    Element *cible;
    Element *boule;
    Element *camera;
    Element *bouleenlair;

};

#endif // MYOPENGL_H

