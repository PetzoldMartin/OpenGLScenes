#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtGui/QGuiApplication>
#include <QOpenGLFramebufferObject>

#include "render/window_gl.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    WindowGL myWindowGL;

    QObject::connect(&myWindowGL,&QQuickWindow::sceneGraphInitialized,&myWindowGL,&WindowGL::OnsceneGraphInitialized,Qt::DirectConnection);
    QObject::connect(&myWindowGL, &QQuickWindow::beforeRendering, &myWindowGL, &WindowGL::OnBeforeQt, Qt::DirectConnection);
    QObject::connect(&myWindowGL,&QQuickWindow::afterRendering,&myWindowGL,&WindowGL::OnafterRendering,Qt::DirectConnection);

    myWindowGL.setSource(QUrl(QStringLiteral("qrc:///qml/main.qml")));
    myWindowGL.show();

    return app.exec();
}
