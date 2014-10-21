#ifndef WINDOW_GL_H
#define WINDOW_GL_H

#include <QQuickItem>

class RenderEngine;

class WindowGL : public QQuickItem
{
    Q_OBJECT

public:
    WindowGL();

signals:

public slots:

    //global
    void rotateView(int x,int y);
    void scaleView (int delta);
    void setViewMode(int viewMode);
    void setMousePose(int x, int y);
    void toggleRenderMode();

    //object
    int pickObjectAt();
    void deselect();
    void rotateObject(int deltax,int deltay,int deltaz);
    void scaleObject(float factor);
    void shiftObject(int dx, int dy, int dz);
    void forceModification();
    void createBlock(float sx, float sy, float sz, float tx, float ty, float tz, float cr, float cg, float cb);
    void createSphere(float sx, float sy, float sz, float tx, float ty, float tz, float cr, float cg, float cb);

    void initialize();
    void update();
    void render();
    void cleanup();
    void sync();
    void windowChanged();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
//    QMatrix4x4* vieport;
    RenderEngine* m_engine;
};

#endif // WINDOW_GL_H
