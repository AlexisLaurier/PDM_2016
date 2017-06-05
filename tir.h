#ifndef TIR_H
#define TIR_H
#include "element.h"


class tir
{
public:
    tir();
    int tirer();
    void setcible(Element* elm){cible=elm;}
    void setbouleenlair(Element* elm){bouleenlair=elm;}
    void setboule(Element* elm){boule=elm;}
    void settrebuchet(Element* elm){trebuchet=elm;}
private:
    bool surtrebuchet;

    Element* cible;
    Element* bouleenlair;
    Element* boule;
    Element* trebuchet;
};

#endif // TIR_H
