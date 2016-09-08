#ifndef CURVE_HPP
#define CURVE_HPP

#include <QVector>
#include <QVector3D>

namespace lab1
{
    typedef struct Curve
    {
        QVector<QVector3D> points;

        struct Parameters
        {
            int steps;
            double t0, tn;
            double r, c;

            Parameters(int steps = 100, double t0 = 0, double tn = 2 * M_PI * 4, double r = 10, double c = 3):
                steps(steps), t0(t0), tn(tn), r(r), c(c) {}

        } params;

        double fx(double alpha) { return params.r * cos(alpha); }
        double fy(double alpha) { return params.r * sin(alpha); }
        double fz(double t)     { return params.c * t;          }

        void calculate()
        {
            points.clear();

            double dt = (params.tn - params.t0) / params.steps;
            for(int i = 0; i <= params.steps; ++i)
            {
                double t = i * dt;
                points.push_back(QVector3D(
                    fx(t),
                    fy(t),
                    fz(t)
                ));
            }
        }
    } Curve;
}

#endif // CURVE_HPP
