#include "window_gl.h"
#include "src/render/render_engine.h"
#include "src/io/console.h"

#include <iostream>
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>


using namespace std;

WindowGL::WindowGL()
    : m_t(0)
    , m_thread_t(0)
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
        connect(win, SIGNAL(activeChanged()), this, SLOT(windowChanged()), Qt::DirectConnection);
        connect(win, SIGNAL(beforeRendering()), this, SLOT(Render()), Qt::DirectConnection);
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(Sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInitialized()), this, SLOT(Initialize()), Qt::DirectConnection);

        win->setClearBeforeRendering(false);
    }
}

void WindowGL::windowChanged() {
    float h = (float)window()->size().height();
    float w = (float)window()->size().width();
    m_engine->Resize(w,h);
}

void WindowGL::Initialize()
{
    Console::Write("Initialize RenderEngine");
    m_engine = new RenderEngine(parent()->parent());


    connect(window()->openglContext(), SIGNAL(aboutToBeDestroyed()), this, SLOT(Cleanup()), Qt::DirectConnection);
}



void WindowGL::Render()
{
    m_engine->Render();
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
