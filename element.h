#ifndef ELEMENT_H
#define ELEMENT_H


class Element
{

public:
    Element();
private:
    //coordonnée selon x
    double x;
    //coordonée selon y
    double y;
    //coordonée selon z
    double z;
    //rotation selon l'axe x
    double c;
    //rotation selon l'axe y
    double u;
    //rotation selon l'axe z
    double e;
    //echelle de l'objet
    double size;
    //booléen permettant de gérer l'affichage d'un element lors du rendu opengl
    bool displayed;
public:
    //get et set sur les champs
    double getx();
    double gety();
    double getz();
    double getc();
    double getu();
    double gete();
    double getsize();
    bool getdisplayed();
    //permet de translater et de déplacer l'élément graphique
    void setpos(double i,double o, double p);
    //permet de faire pivoter l'element graphique
    void setrot(double n, double m, double l);
    //permet de définir la taille de l'objet
    void setsize(double n){size=n;}
    //permet de définir si un objet est affiché
    void setdisplayed(bool choice){displayed=choice;}
};

#endif // ELEMENT_H

