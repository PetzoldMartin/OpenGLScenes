#include "window_gl.h"
#include "src/render/render_engine.h"
#include "src/io/console.h"

#include <iostream>
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>

using namespace std;

WindowGL::WindowGL()
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void WindowGL::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, SIGNAL(afterRendering()), this, SLOT(update()),Qt::DirectConnection);
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(windowChanged()), Qt::DirectConnection);
        connect(win, SIGNAL(beforeRendering()), this, SLOT(render()), Qt::DirectConnection);
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInitialized()), this, SLOT(initialize()), Qt::DirectConnection);

        win->setClearBeforeRendering(false);
    }
}

void WindowGL::windowChanged() {
    float h = (float)window()->size().height();
    float w = (float)window()->size().width();
    m_engine->Resize(w,h);
}

void WindowGL::initialize()
{
    Console::Write("Initialize RenderEngine");
    m_engine = new RenderEngine(parent()->parent());


    connect(window()->openglContext(), SIGNAL(aboutToBeDestroyed()), this, SLOT(cleanup()), Qt::DirectConnection);
}

void WindowGL::update()
{
    window()->update();
}



void WindowGL::render()
{
    m_engine->Render();
}

void WindowGL::cleanup()
{
    //TODO: DELETE SHIT
}


// Copy the state of the object in the
// GUI thread into the rendering thread.
void WindowGL::sync()
{
    //m_thread_t = m_t;
}
