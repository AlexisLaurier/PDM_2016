#include "element.h"

Element::Element()
{
x=0;
y=0;
z=0;
c=0;
u=0;
e=0;
size=1;
displayed=false;
}
double Element::getx()
{
   return x;
}

double Element::gety()
{
   return y;
}
double Element::getz()
{
   return z;
}
double Element::getc()
{
   return c;
}
double Element::getu()
{
   return u;
}
double Element::gete()
{
   return e;
}
double Element::getsize()
{
   return size;
}
bool Element::getdisplayed()
{
   return displayed;
}
void Element::setpos(double i,double o, double p)
{
    x=i;
    y=o;
    z=p;
}

void Element::setrot(double n, double m, double l)
{
    c=n;
    u=m;
    e=l;
}
