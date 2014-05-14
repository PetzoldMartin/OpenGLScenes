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
    int pickObjectId(int x, int y);
    void rotate(int id,int x,int y);
    void scale (int delta);

    void initialize();
    void update();
    void render();
    void cleanup();
    void sync();
    void windowChanged();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    RenderEngine* m_engine;
};

#endif // WINDOW_GL_H
