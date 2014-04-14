#ifndef WINDOW_GL_H
#define WINDOW_GL_H

#include <QtGui/QGuiApplication>
#include <QOpenGLFramebufferObject>
#include <QtQuick/QQuickView>
#include <QQmlApplicationEngine>

class WindowGL : public QQuickView
{
private:
    QOpenGLFramebufferObject *fbo;
public slots:
    void OnsceneGraphInitialized();
    void OnafterRendering();
};

#endif // WINDOW_GL_H
