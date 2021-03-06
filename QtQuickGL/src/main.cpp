#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "render/window_gl.h"
#include "render/object/collada.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<WindowGL>("OpenGLUnderQML", 1, 0, "WindowGL");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///qml/main.qml"));
    view.show();

    QObject::connect((QObject*)view.engine(), SIGNAL(quit()), &app, SLOT(quit()));


    return app.exec();
}
