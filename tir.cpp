#include "tir.h"
#include <QTimer>
using namespace std;
Tir::Tir()
{
surtrebuchet=true;
}


int Tir::tirer()
{
boule->setdisplayed(true);
bouleenlair->setdisplayed(false);

//mouvement jusqu'à la verticale
time=0;
QTimer *timer = new QTimer(this);
connect(timer, SIGNAL(timeout()),this, SLOT(updatetime()));
timer->start(10);
int puissance =trebuchet->getu();
while(trebuchet->gete()>=-20){

    if(trebuchet->getu()>=0)
    trebuchet->setrot(trebuchet->getc(),puissance-time*time, 0);
    else trebuchet->setrot(trebuchet->getc(),0, -time*0.1);
}

//mouvement jusqu'à la cible

time=0;
while(tirencours==true){
}
timer->stop();

time=0;
while(time<1000){};

}

void Tir::updatetime()
{time+=10;}
