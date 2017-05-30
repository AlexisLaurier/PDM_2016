#ifndef ELEMENT_H
#define ELEMENT_H


class Element
{

public:
    Element();
private:
    double x;
    double y;
    double z;
    double c;
    double u;
    double e;
    double size;
    bool displayed;
public:
    double getx();
    double gety();
    double getz();
    double getc();
    double getu();
    double gete();
    double getsize();
    bool getdisplayed();
    void setpos(double i,double o, double p);
    void setrot(double n, double m, double l);
    void setsize(double n){size=n;}
    void setdisplayed(bool choice){displayed=choice;}
};

#endif // ELEMENT_H

