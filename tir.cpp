#include "tir.h"
#include <QTimer>
#include <QtWidgets>
#include <QtMath>
using namespace std;
Tir::Tir(QWidget *parent) : QLabel(parent)
{
    cpt_ = 0;
    time = 0;
}


int Tir::tirer()
{
boule->setdisplayed(true);
bouleenlair->setdisplayed(false);
surtrebuchet=true;
//mouvement jusqu'à la verticale
if (cpt_ == 0){
    time=0;
    cpt_++;
    puissance =trebuchet->getu();
}



    if(trebuchet->getu()>-90){
        trebuchet->setrot(trebuchet->getc(),puissance-time*time*0.00001, trebuchet->gete());
        emit changementOpenGl();
        return 0;

    }

    if(trebuchet->gete()>-20) {
        trebuchet->setrot(trebuchet->getc(),-90, -puissance-time*0.01);
        emit changementOpenGl();
        qDebug() << "le drap tourne";
        return 0;

    }

if(bouleenlair->getz()>0)
{
    qDebug() << "suis en lair";
    surtrebuchet=false;
    if(cpt_==1) {time=0; cpt_++;}
    boule->setdisplayed(false);
    bouleenlair->setdisplayed(true);
    bouleenlair->setsize(1);
    bouleenlair->setpos(qSin(-trebuchet->getc())*puissance*time*0.01,qCos(trebuchet->getc())*puissance*time*0.01,-0.0005*time*time*0.001+puissance*time*0.01+0.2);
    return 0;
}

//mouvement jusqu'à la cible
/*
time=0;
while(tirencours==true){
}

time=0;
while(time<1000){};*/
cpt_ = 0;
return 3;
}

void Tir::updatetime()
{time+=10;}
