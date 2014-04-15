#ifndef WINDOW_GL_H
#define WINDOW_GL_H

#include <QtGui/QGuiApplication>
#include <QOpenGLFramebufferObject>
#include <QtQuick/QQuickView>
#include <QQmlApplicationEngine>
#include <QOpenGLShaderProgram>

class WindowGL : public QQuickView
{
private:
    QOpenGLFramebufferObject *fbo_render;
    QOpenGLShaderProgram* shader;
public slots:
    WindowGL();
    void OnsceneGraphInitialized();
    void OnafterQt();
    void OnBeforeQt();
};

#endif // WINDOW_GL_H
