#include "tir.h"
#include <QTimer>
#include <QtWidgets>
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

if(trebuchet->gete()>=-20){

    if(trebuchet->getu()>-90){
        trebuchet->setrot(trebuchet->getc(),puissance-time*time*0.00001, 0);
        emit changementOpenGl();
        return 0;

    }

    else {
        trebuchet->setrot(trebuchet->getc(),0, -time*0.1*0.001);
        emit changementOpenGl();
        return 0;

    }
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
