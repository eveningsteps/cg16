#ifndef WINDOW_H
#define WINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>

#include <QTimer>
#include <QVector>

class Window: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
    void initializeGL();
    void paintGL();

    QOpenGLShaderProgram ps;
    QOpenGLTexture *texture;

    QTimer timer;
    size_t frame;

    GLuint vbo_particles, vbo_random;

    int particles;
};

#endif // WINDOW_H
