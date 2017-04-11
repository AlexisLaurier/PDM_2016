// myopengl.h

#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QGLWidget>
#include "terrain.h"

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

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setXTranslation(double move);
    void setYTranslation(double move);
    void setZTranslation(double move);


signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:

    int xRot;
    int yRot;
    int zRot;
    double xTrans;
    double yTrans;
    double zTrans;

    QPoint lastPos;
    Terrain *terrain;
};

#endif // MYOPENGL_H

