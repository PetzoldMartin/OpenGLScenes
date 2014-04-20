#include "window_gl.h"
#include <iostream>
#include <QtQuick/QQuickWindow>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>


using namespace std;

WindowGL::WindowGL()
    //: m_t(0)
    //, m_thread_t(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}


void WindowGL::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void WindowGL::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, SIGNAL(beforeRendering()), this, SLOT(Render()), Qt::DirectConnection);
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(Sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInitialized()), this, SLOT(Initialize()), Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void WindowGL::Initialize()
{
    cout << "SceneGraphInitialized" << endl;
    //fbo_render = new QOpenGLFramebufferObject(200,150,QOpenGLFramebufferObject::CombinedDepthStencil, GL_TEXTURE_2D,GL_RGBA8);
    //setRenderTarget(fbo_render);
    shader = new QOpenGLShaderProgram(parent());
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, QString("data/shader/basic.frag"));
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, QString("data/shader/basic.vert"));
    shader->link();

    // test
    for(int i = 10; i >= 0; --i) {
        cout << i << endl;
    }

    connect(window()->openglContext(), SIGNAL(aboutToBeDestroyed()), this, SLOT(Cleanup()), Qt::DirectConnection);
}



void WindowGL::Render()
{
    shader->bind();

    glBegin(GL_QUADS);
    {
        glVertex2d(1.0,1.0);
        glVertex2d(-1.0,1.0);
        glVertex2d(-1.0,-1.0);
        glVertex2d(1.0,-1.0);
    }
    glEnd();

    shader->release();
}

void WindowGL::Cleanup()
{
    //TODO: DELETE SHIT
}


// Copy the state of the object in the
// GUI thread into the rendering thread.
void WindowGL::Sync()
{
    m_thread_t = m_t;
}
