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

        // update loop
        connect(win, SIGNAL(afterRendering()),this, SLOT(update()), Qt::DirectConnection);

        win->setClearBeforeRendering(false);
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
    m_engine->Render(true);
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

void WindowGL::setMousePose(int x, int y)
{
    m_engine->setMousePose(x, y);
}

void WindowGL::toggleRenderMode()
{
    m_engine->toggleRenderMode();
}

void WindowGL::rotateView (int dx,int dy) {
    m_engine->rotateView(dx,dy);
}

int WindowGL::pickObjectAt() {
    return m_engine->pickObjectAt();
}
void WindowGL::deselect(){
    m_engine->deselect();
}

void WindowGL::rotateObject(int deltax,int deltay,int deltaz) {
    m_engine->rotateObject(deltax,deltay,deltaz);
}

void WindowGL::scaleObject(float factor) {
    m_engine->scaleObject(factor);
}

void WindowGL::shiftObject( int dx, int dy, int dz){
    m_engine->translateObject(dx,dy,dz);

}
void WindowGL::forceModification(){
    m_engine->forceModification();
}

void WindowGL::createBlock(float sx, float sy, float sz, float tx, float ty, float tz, float cr, float cg, float cb)
{
    m_engine->CreateBlock(QVector3D(sx,sy,sz),QVector3D(tx,ty,tz), QVector4D(cr,cg,cb,1.0));
}

void WindowGL::createSphere(float sx, float sy, float sz, float tx, float ty, float tz, float cr, float cg, float cb)
{
    m_engine->CreateSphere(QVector3D(sx,sy,sz),QVector3D(tx,ty,tz), QVector4D(cr,cg,cb,1.0));
}

// Copy the state of the object in the
// GUI thread into the rendering thread.
void WindowGL::sync()
{
    //TODO Sync Shit!!!
}
