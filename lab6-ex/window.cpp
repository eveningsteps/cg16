#include "window.h"
#include <vector>
#include <cstdlib>
#include <ctime>

Window::Window(QWidget *parent):
    QOpenGLWidget(parent),
    frame(0),
    particles(300)
{
    srand(time(0));
}

void Window::initializeGL()
{
    initializeOpenGLFunctions();

    ps.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/particle.vert");
    ps.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/particle.frag");
    ps.link();

    std::vector<float> v, r;
    int density = 2000;
    for(int i = 0; i < particles; ++i)
    {
        v.push_back(float(i));
        for(int j = 0; j < 3; ++j)
        {
            float rr = rand() % (density + 1); // -> [0 .. X]
            rr -= density / 2.0; // -> [-X/2 .. X/2]
            rr /= density / 2.0; // -> [-1 .. 1]
            r.push_back(rr);
        }
    }

    glGenBuffers(1, &vbo_particles);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_particles);
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(v[0]), v.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &vbo_random);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_random);
    glBufferData(GL_ARRAY_BUFFER, r.size() * sizeof(r[0]), r.data(), GL_STATIC_DRAW);

    texture = new QOpenGLTexture(QImage(":/particle.png"));

    timer.setInterval(15);
    timer.setSingleShot(false);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start();
}

void Window::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_POINT_SPRITE);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glPointSize(20);

    texture->bind();

    ps.bind();
    ps.setUniformValue("time", float(frame));
    ps.setUniformValue("sampler", 0);

    GLuint att_random = ps.attributeLocation("random");
    glEnableVertexAttribArray(att_random);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_random);
    glVertexAttribPointer(att_random, 3, GL_FLOAT, GL_TRUE, 0, 0);

    GLuint att_particles = ps.attributeLocation("vertex");
    glEnableVertexAttribArray(att_particles);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_particles);
    glVertexAttribPointer(att_particles, 1, GL_FLOAT, GL_TRUE, 0, 0);

    glDrawArrays(GL_POINTS, 0, particles);

    ps.release();
    frame = (frame + 1) % 1000;
}

Window::~Window()
{
}

