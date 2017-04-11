#include "terrain.h"
#include <QGLWidget>
#include <QImage>
#include <QDebug>


Terrain::Terrain(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

}


void Terrain::draw(){
    texture_herbe = new QOpenGLTexture(QImage(":/ressources/textures/herbe.bmp").mirrored());
    texture_filet = new QOpenGLTexture(QImage(":/ressources/textures/filet.bmp").mirrored());


    glDepthFunc(GL_LEQUAL);
    glEnable ( GL_NORMALIZE );
    glDepthMask ( GL_TRUE );
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    glPointSize ( 1.0f );
    glLineWidth ( 1.0f );
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix ();
    glColor3f(1,1,1);
    glEnable( GL_TEXTURE_2D );
    // BIND TEXTURE
    texture_herbe->bind();
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
    // BIND TEXTURE
    texture_filet->bind();
    glBegin(GL_QUADS);
    glTexCoord2f (0,0);
    glVertex3f(-0.7,-0.7,0.02);
    glTexCoord2f (1,0);
    glVertex3f(-0.7,1.5,0.02);
    glTexCoord2f (1,1);
    glVertex3f(-0.7,1.5,0.5);
    glTexCoord2f (0,1);
    glVertex3f(-0.7,-0.7,0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f (0,0);
    glVertex3f(-0.7,1.5,0.02);
    glTexCoord2f (1,0);
    glVertex3f(0.7,1.5,0.02);
    glTexCoord2f (1,1);
    glVertex3f(0.7,1.5,0.5);
    glTexCoord2f (0,1);
    glVertex3f(-0.7,1.5,0.5);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f (0,0);
    glVertex3f(0.7,1.5,0.02);
    glTexCoord2f (1,0);
    glVertex3f(0.7,-0.7,0.02);
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
