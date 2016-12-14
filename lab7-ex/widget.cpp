#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QPointF>
#include <QPainter>

#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(repaint()));
}

Widget::~Widget()
{
    delete ui;
}

double N(const vector<int> &T, int i, int order, float t)
{
    // the inequality should be as follows: T[i] <= t <= T[i+1],
    // but I figured I don't really want to fiddle with "correct" floating point numbers comparsion
    // and will play lazy and just add the very last anchor point to the list of a spline's values

    // of course, it absolutely WILL backfire when last (order) knots are not equal, but.. oh well.

    if(order == 1)
        return T.at(i) <= t && t < T.at(i+1);

    double nA = t - T.at(i);
    double dA = T.at(i + order - 1) - T.at(i);

    double nB = T.at(i + order) - t;
    double dB = T.at(i + order) - T.at(i+1);

    double A = (dA == 0)? 0 : nA / dA;
    double B = (dB == 0)? 0: nB / dB;
    return A * N(T, i, order - 1, t) + B * N(T, i + 1, order - 1, t);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    int anchors_cnt = 7;
    int order = 4;
    int steps = 100;

    // for a spline to go through the first and last control points,
    // its first and last (order) knots are required to be the same
    // (see the note about knots multiplicity @ wiki)

    // a possible set of knots is:
    // [0] x k * [1 .. N - k - 2] + [N - k - 1] * k
    // where N is the number of control points and k is the spline's degree
    vector<int> knots;
    for(int i = 0; i < order; ++i)
        knots.push_back(0);
    for(int i = 1; i < anchors_cnt - (order - 1); ++i)
        knots.push_back(i);
    for(int i = 0; i < order; ++i)
        knots.push_back(anchors_cnt - (order - 1));

    // why not use random control points for a good example?
    vector<QPointF> anchor_points;
    for(int i = 0; i < anchors_cnt; ++i)
    {
        double rx = rand() % width();
        double ry = rand() % height();
        anchor_points.push_back(QPointF(rx, ry));
    }

    // makes everything a bit more clear
    painter.setPen(QColor(Qt::gray));
    for(int i = 0; i < anchors_cnt; ++i)
    {
        if(i > 0)
            painter.drawLine(anchor_points[i-1], anchor_points[i]);
        painter.drawEllipse(anchor_points[i], 2, 2);
    }

    // calculate the spline itself
    vector<QPointF> res;
    for(int s = 0; s < steps; ++s)
    {
        double t = s / float(steps) * order;
        QPointF pt(0.0, 0.0);
        for(int i = 0; i < anchors_cnt; ++i)
            pt += N(knots, i, order, t) * anchor_points[i];
        res.push_back(pt);
    }

    // see note regarding inequality in N() function at the top
    res.push_back(anchor_points.back());

    painter.setPen(QColor(Qt::red));
    for(int i = 0; i < (int)res.size() - 1; ++i)
        painter.drawLine(res[i], res[i+1]);
}
