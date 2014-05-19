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

    //object
    int pickObjectAt(int x, int y);
    void rotateObject(int id,int dx,int dy);

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
