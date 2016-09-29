#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMatrix4x4>
#include <QPointF>
#include <QVector>
#include <QtMath>

#include "tetraeder.hpp"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void scaleChanged(int);

private:
    Ui::Widget *ui;

    Tetraeder tetraeder;

    int prev_mx, prev_my;
    double phi_x, phi_y;

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // WIDGET_H
