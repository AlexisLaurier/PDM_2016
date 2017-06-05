#ifndef TIR_H
#define TIR_H
#include "element.h"
#include <QLabel>

class tir : public QLabel
{

public:
    tir();
    int tirer();
    void setcible(Element* elm){cible=elm;}
    void setbouleenlair(Element* elm){bouleenlair=elm;}
    void setboule(Element* elm){boule=elm;}
    void settrebuchet(Element* elm){trebuchet=elm;}

public slots:
    void increment();
private:
    bool surtrebuchet;
    bool tirencours;
    Element* cible;
    Element* bouleenlair;
    Element* boule;
    Element* trebuchet;
    int time;

};

#endif // TIR_H
