#ifndef ELEMENT_H
#define ELEMENT_H


class element
{

public:
    element();
private:
    double x;
    double y;
    double z;
    double c;
    double u;
    double e;
    double size;
public:
    double getx();
    double gety();
    double getz();
    double getc();
    double getu();
    double gete();
    double getsize();
    void setx(double n);
    void sety(double n);
    void setz(double n);
    void setc(double n);
    void setu(double n);
    void sete(double n);
    void setsize(double n);
};

#endif // ELEMENT_H
