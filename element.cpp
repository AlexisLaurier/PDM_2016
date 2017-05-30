#include "element.h"

element::element()
{
x=0;
y=0;
z=0;
c=0;
u=0;
e=0;
}
double element::getx()
{
   return x;
}

double element::gety()
{
   return y;
}
double element::getz()
{
   return z;
}
double element::getc()
{
   return c;
}
double element::getu()
{
   return u;
}
double element::gete()
{
   return e;
}
void element::setx(double n)
{
    x=n;
}

void element::sety(double n)
{
    y=n;
}
void element::setz(double n)
{
    z=n;
}
void element::setc(double n)
{
    c=n;
}
void element::setu(double n)
{
    u=n;
}
void element::sete(double n)
{
    e=n;
}
