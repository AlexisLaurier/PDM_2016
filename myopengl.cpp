// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>
#include <QGLWidget>
#include "GL/glu.h"
#include "myopengl.h"

MyOpenGl::MyOpenGl(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
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

QSize MyOpenGl::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyOpenGl::sizeHint() const
{
    return QSize(400, 400);
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
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
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

    draw();
}

void MyOpenGl::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    gluPerspective(25, 1, 1, 80);
#else
    gluPerspective(25, 1, 1, 80);
#endif
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

void MyOpenGl::draw()
{



    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glEnable ( GL_NORMALIZE );
    glDepthMask ( GL_TRUE );
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    glPointSize ( 1.0f );
    glLineWidth ( 1.0f );
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix ();
    glColor3f(1,1,1);
    glEnable( GL_TEXTURE_2D );
    /* BIND TEXTURE */
   // glBindTexture(GL_TEXTURE_2D, GLtexture[0]);
    glBegin(GL_QUADS);
    glTexCoord2f (100,0);
    glVertex3f(10,-10,0);
    glTexCoord2f (100,100);
    glVertex3f(10,10,0);
    glTexCoord2f (0,100);
    glVertex3f(-10,10,0);
    glTexCoord2f (0,0);
    glVertex3f(-10,-10,0);
    glEnd();
    glDisable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glDepthMask (GL_FALSE);
    glEnable( GL_TEXTURE_2D );
    glColor4f(1,1,1,0.4);
    /* BIND TEXTURE */
   // glBindTexture(GL_TEXTURE_2D, GLtexture[1]);
    glBegin(GL_QUADS);
    glTexCoord2f (0,0);
    glVertex3f(-0.7,-0.7,0.1);
    glTexCoord2f (1,0);
    glVertex3f(-0.7,1.5,0.1);
    glTexCoord2f (1,1);
    glVertex3f(-0.7,1.5,0.5);
    glTexCoord2f (0,1);
    glVertex3f(-0.7,-0.7,0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f (0,0);
    glVertex3f(-0.7,1.5,0.1);
    glTexCoord2f (1,0);
    glVertex3f(0.7,1.5,0.1);
    glTexCoord2f (1,1);
    glVertex3f(0.7,1.5,0.5);
    glTexCoord2f (0,1);
    glVertex3f(-0.7,1.5,0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f (0,0);
    glVertex3f(0.7,1.5,0.1);
    glTexCoord2f (1,0);
    glVertex3f(0.7,-0.7,0.1);
    glTexCoord2f (1,1);
    glVertex3f(0.7,-0.7,0.5);
    glTexCoord2f (0,1);
    glVertex3f(0.7,1.5,0.5);
    glEnd();
    glDisable( GL_TEXTURE_2D );
    glDepthMask (GL_TRUE);
    glDisable( GL_BLEND );
    glPopMatrix ();
}
