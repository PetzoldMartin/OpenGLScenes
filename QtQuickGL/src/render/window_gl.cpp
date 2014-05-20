#include "window_gl.h"
#include "src/render/render_engine.h"
#include "src/io/console.h"

#include <iostream>
#include <QQuickWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QThread>
#include <QSurfaceFormat>
#include <QTimer>

using namespace std;

WindowGL::WindowGL()
{
    m_engine = NULL;
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void WindowGL::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        // TODO: This cool windowchange Crashes =(
        //connect(win, SIGNAL(xChanged(int)), this, SLOT(windowChanged()), Qt::DirectConnection);
        //connect(win, SIGNAL(yChanged(int)), this, SLOT(windowChanged()), Qt::DirectConnection);
        // TODO: But this dirty one works
        connect(win, SIGNAL(beforeRendering()), this, SLOT(windowChanged()), Qt::DirectConnection);

        connect(win, SIGNAL(beforeRendering()), this, SLOT(render()), Qt::DirectConnection);
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInitialized()), this, SLOT(initialize()), Qt::DirectConnection);

        win->setClearBeforeRendering(false);

        // Set some formats
        QSurfaceFormat f;
        f.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
        f.setSamples(4);
        f.setDepthBufferSize(1000000);
        win->setFormat(f);

    }
}

void WindowGL::windowChanged() {
    // qDebug() << "resize";
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
    m_engine->Update();
    window()->update();
}



void WindowGL::render()
{
    m_engine->Render();
    window()->update();
}
void WindowGL::cleanup()
{
    delete m_engine;
}

void WindowGL::scaleView (int delta) {
    m_engine->scaleView(delta);
}

void WindowGL::setViewMode(int viewMode)
{
    m_engine->setViewMode(viewMode);
}

void WindowGL::rotateView (int dx,int dy) {
    m_engine->rotateView(dx,dy);
}

int WindowGL::pickObjectAt(int x, int y) {
    return m_engine->pickObjectAt(x,y);
}

void WindowGL::rotateObject(int id,int dx,int dy) {
    m_engine->rotateObject(id,dx,dy);
}

// Copy the state of the object in the
// GUI thread into the rendering thread.
void WindowGL::sync()
{
    //TODO Sync Shit!!!
}
