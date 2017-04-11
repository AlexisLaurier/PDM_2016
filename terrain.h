#ifndef TERRAIN_H
#define TERRAIN_H
#include <QGLWidget>
#include <QtOpenGL/QGLWidget>
#include <QOpenGLTexture>

class Terrain : public QGLWidget
{

public:
    explicit Terrain(QWidget *parent=0);

protected:
    //void initializeGL();

public:
    void draw();

private:
    GLuint textures[2];
    QOpenGLTexture *texture_herbe;
    QOpenGLTexture *texture_filet;
};

#endif // TERRAIN_H
