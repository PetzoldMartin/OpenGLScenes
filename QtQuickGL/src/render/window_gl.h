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

    //object
    int pickObjectAt();
    void rotateObject(int id,int dx,int dy);
    void scaleObject(int id,int factor);
    void shiftObject(int id,int dx,int dy,int dz);
    void createBlock(float sx, float sy, float sz, float tx, float ty, float tz, float cr, float cg, float cb);

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
