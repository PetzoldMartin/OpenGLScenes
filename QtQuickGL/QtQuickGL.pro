TEMPLATE = app

QT += qml quick

SOURCES += \
    src/render/window_gl.cpp \
    src/main.cpp \
    src/render/render_engine.cpp \
    src/render/object/drawable.cpp \
    src/io/console.cpp \
    src/render/object/factory.cpp \
    src/render/scene/scene.cpp \
    src/render/scene/test_scene.cpp \
    src/render/object/mesh.cpp

RESOURCES += \
    rsc/resource.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/render/window_gl.h \
    src/render/render_engine.h \
    src/render/object/drawable.h \
    src/io/console.h \
    src/render/object/factory.h \
    src/render/scene/scene.h \
    src/render/scene/test_scene.h \
    src/render/object/mesh.h

OTHER_FILES += \
    rsc/qml/main.qml \
    rsc/shader/basic.frag \
    rsc/shader/basic.vert \
