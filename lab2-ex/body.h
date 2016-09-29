#ifndef BODY_H
#define BODY_H

#include <QVector3D>
#include <QVector>
#include <QMatrix4x4>
#include <QPainter>

struct Triangle
{
    QVector3D a, b, c;
    Triangle(QVector3D a = QVector3D(), QVector3D b = QVector3D(), QVector3D c = QVector3D()): a(a), b(b), c(c){}

    QVector3D normal();
    bool isVisible();
};

Triangle operator*(QMatrix4x4 m, Triangle t);

struct Body
{
    QVector<Triangle> faces;
    Body(){}
    virtual ~Body(){}

    virtual void calculate(){}
    void draw(QPainter *p);
};

Body operator*(QMatrix4x4 m, Body b);

#endif // BODY_H
