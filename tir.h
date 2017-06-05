#ifndef TIR_H
#define TIR_H
#include "element.h"
#include <QWidget>
#include <QLabel>

class Tir : public QLabel
{
    Q_OBJECT
public:
    Tir(QWidget *parent = 0);
    int tirer();
    void setcible(Element* elm){cible=elm;}
    void setbouleenlair(Element* elm){bouleenlair=elm;}
    void setboule(Element* elm){boule=elm;}
    void settrebuchet(Element* elm){trebuchet=elm;}

public slots:
    void updatetime();
signals:
    void changementOpenGl();
private:
    bool surtrebuchet;
    bool tirencours;
    Element* cible;
    Element* bouleenlair;
    Element* boule;
    Element* trebuchet;
    int time;
    int cpt_;

};

#endif // TIR_H
