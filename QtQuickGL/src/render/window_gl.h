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
