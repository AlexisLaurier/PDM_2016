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
    //fonction gérant opengl
    //permet d'itinialiser la scène opengl et de charger les textures utilisées
    void initializeGL();
    //lance le rendu de la scène opengl
    void paintGL();
    //est utilisé quand la fenêtre graphique est redimensionnée
    void resizeGL(int width, int height);

public slots:
    //permet de stocker dans les champs des pointeurs vers les divers élements composant la scène
    void settrebuchet(Element* elm) {trebuchet = elm;}
    void setboule(Element* elm){boule=elm;}
    void setbouleenlair(Element* elm){bouleenlair=elm;}
    void setcible(Element* elm){cible=elm;}
    void setcamera(Element* elm){camera=elm;}


private:


    //stockage en mémorie des textures lors de la construction d'un objet myopengl
    QOpenGLTexture *textures[7];
    QPoint lastPos;
    //champs des pointeurs vers les divers élements composant la scène
    QWidget *parent_;
    Element *trebuchet;
    Element *cible;
    Element *boule;
    Element *camera;
    Element *bouleenlair;

};

#endif // MYOPENGL_H

