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
    //lance l'animation de tir et retourne le score réalise
    int tirer();
    //permet de construire un élement tir en indiquant un pointeur vers les élements de la scène
    void setcible(Element* elm){cible=elm;}
    void setbouleenlair(Element* elm){bouleenlair=elm;}
    void setboule(Element* elm){boule=elm;}
    void settrebuchet(Element* elm){trebuchet=elm;}
signals:
    //permet de lancer un rendu openGL lors de la modification des élements constituant la scène
    void changementOpenGl();
public slots:
    void updatetime();
private:
    //booléen permetant de switcher entre l'afficher de boule et de bouleenlair, qui sont 2 éléments graphiques différent car dans des système de coordonées différent

    bool surtrebuchet;
    bool tirencours;
    Element* cible;
    Element* bouleenlair;
    Element* boule;
    Element* trebuchet;
    //stockage de la date depuis le debut du tir en cours
    int time;
    //variable permettant de réinitaliser le time au cours du mouvement
    int cpt_;
    //stocke la puissance choisie par l'utilisateur pour le tir
    int puissance;

};

#endif // TIR_H
