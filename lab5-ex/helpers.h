#ifndef HELPERS
#define HELPERS

#include <QVector3D>

namespace helpers
{
	static const float inf = -1e9;
}

inline float clamp(float x, float a, float b)
{
	if (x < a) return a;
	if (x > b) return b;
	return x;
}

inline bool XbetweenAB(float x, float a, float b)
{
	return a <= x && x <= b;
}

inline float rayXplane(QVector3D from, QVector3D to,
					   QVector3D A, QVector3D N,
					   QVector3D *result, float *t)
{
	float denom = QVector3D::dotProduct(N, from - to);
	if(denom * denom < 1e-4)
		return helpers::inf;

	*t = QVector3D::dotProduct(from - A, N) / denom;
	QVector3D add = (from - to);
	add *= *t;
	*result = from + add;
}

inline float rayXtriangle(QVector3D from, QVector3D to,
						  QVector3D A, QVector3D B, QVector3D C,
						  QVector3D *result, float *t)
{
	QVector3D N;
	N = QVector3D::crossProduct(A-B, A-C);

	if (rayXplane(from, to, A, N, result, t) < 0)
		return helpers::inf;

	if(QVector3D::dotProduct(QVector3D::crossProduct(A-B, A-C), QVector3D::crossProduct(A-B, A - *result)) < 0)
		return helpers::inf;

	if(QVector3D::dotProduct(QVector3D::crossProduct(B-C, B-A), QVector3D::crossProduct(B-C, B - *result)) < 0)
		return helpers::inf;

	if(QVector3D::dotProduct(QVector3D::crossProduct(C-A, C-B), QVector3D::crossProduct(C-A, C - *result)) < 0)
		return helpers::inf;

	return *t;
}

#endif // HELPERS

