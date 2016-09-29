#include "body.h"
#include <QDebug>
QVector3D Triangle::normal()
{
    return QVector3D::crossProduct((b - a), (c - a));
}

bool Triangle::isVisible()
{
    // TODO: visibility check!
    return true;
}

Triangle operator*(QMatrix4x4 m, Triangle t)
{
    return Triangle(m * t.a, m * t.b, m * t.c);
}

void Body::draw(QPainter *p)
{
    foreach(Triangle face, faces)
    {
        if(face.isVisible())
        {
            p->drawLine(face.a.toPointF(), face.b.toPointF());
            p->drawLine(face.b.toPointF(), face.c.toPointF());
            p->drawLine(face.c.toPointF(), face.a.toPointF());
        }
    }
}

Body operator*(QMatrix4x4 m, Body b)
{
    Body res;
    foreach(Triangle face, b.faces)
        res.faces.push_back(m * face);

    return res;
}
