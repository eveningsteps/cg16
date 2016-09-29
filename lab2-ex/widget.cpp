#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

int sign(int x)
{
    return x > 0? 1 : x == 0? 0 : -1;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    phi_x = phi_y = 0;
    tetraeder.calculate();

    connect(ui->scaleSlider, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::scaleChanged(int)
{
    repaint();
}

void Widget::paintEvent(QPaintEvent *)
{
    QMatrix4x4 m;
    m.translate(200, 200);
    m.rotate(phi_y, 1, 0, 0);
    m.rotate(phi_x, 0, 1, 0);
    m.scale(ui->scaleSlider->value() / 10.0);

    QPainter p(this);

    Body t = m * tetraeder;
    t.draw(&p);
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    int mx = e->x(), my = e->y();
    phi_x += sign(mx - prev_mx), phi_y += sign(my - prev_my);

    prev_mx = mx, prev_my = my;
    repaint();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    prev_mx = e->x(), prev_my = e->y();
}
