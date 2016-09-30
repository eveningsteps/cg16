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
    curve.calculate();

    ui->spinBox->setValue(curve.params.steps);
    ui->doubleSpinBox->setValue(curve.params.r);

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(stepsChanged(int)));
    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(radiusChanged(double)));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::radiusChanged(double r)
{
    curve.params.r = r;
    curve.calculate();
    repaint();
}

void Widget::stepsChanged(int n)
{
    curve.params.steps = n;
    curve.calculate();
    repaint();
}

void Widget::buttonClicked()
{
    phi_x = phi_y = 0;
    repaint();
}

void Widget::paintEvent(QPaintEvent *)
{
    QMatrix4x4 m;
    m.translate(200, 200);
    m.rotate(phi_x, 1, 0, 0);
    m.rotate(phi_y, 0, 1, 0);
    m.scale(3);

    QPainter p(this);
    for(int i = 0; i < curve.points.size() - 1; ++i)
    {
        QVector3D p0 = m * curve.points[i], p1 = m * curve.points[i+1];
        p.drawLine(p0.toPointF(), p1.toPointF());
    }
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
