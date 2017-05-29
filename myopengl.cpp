// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
#include <QGLWidget>
#include "GL/glu.h"
#include "myopengl.h"

MyOpenGl::MyOpenGl(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    terrain = new Terrain(this);
    xRot = 0;
    yRot = 0;
    zRot = 0;
    xTrans = 0;
    yTrans = 0;
    zTrans = -250;
}

MyOpenGl::~MyOpenGl()
{
}


static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyOpenGl::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyOpenGl::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyOpenGl::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyOpenGl::setXTranslation(double move){
    if (move != xTrans) {
        xTrans = move;
        updateGL();
    }
}

void MyOpenGl::setYTranslation(double move){
    if (move != yTrans) {
        yTrans = move;
        updateGL();
    }
}

void MyOpenGl::setZTranslation(double move){
    if (move != zTrans) {
        zTrans = move;
        updateGL();
    }
}


void MyOpenGl::initializeGL()
{




    qglClearColor(QColor(119, 181, 254));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 100, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyOpenGl::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(xTrans /20 , 0, 0);
    glTranslatef(0 , yTrans /20, 0);
    glTranslatef(0 , 0, zTrans /20);
    glRotatef(xRot % 360, 1.0, 0.0, 0.0);
    glRotatef(yRot % 360, 0.0, 1.0, 0.0);
    glRotatef(zRot % 360, 0.0, 0.0, 1.0);

    terrain->draw();
}

void MyOpenGl::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport(0, (height - side) / 2, width, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, width/(float)height, 0.01, 200);

    glMatrixMode(GL_MODELVIEW);
}

void MyOpenGl::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyOpenGl::wheelEvent(QWheelEvent *event){
    setZTranslation(zTrans + 0.15*event->delta());
}

void MyOpenGl::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 0.5 * dy);
        setYRotation(yRot  + 0.5 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXTranslation(xTrans + 0.2* dx);
        setYTranslation(yTrans + 0.2* (-dy));
    }

    lastPos = event->pos();
}


