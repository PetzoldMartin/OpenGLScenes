#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "render/window_gl.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<WindowGL>("OpenGLUnderQML", 1, 0, "WindowGL");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///qml/main.qml"));
    view.show();


    return app.exec();
}
