#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMatrix4x4>
#include <QPointF>
#include <QVector>
#include <QtMath>

#include "curve.hpp"

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
    void radiusChanged(double r);
    void stepsChanged(int n);
    void buttonClicked();

private:
    Ui::Widget *ui;
    lab1::Curve curve;

    int prev_mx, prev_my;
    double phi_x, phi_y;

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // WIDGET_H
