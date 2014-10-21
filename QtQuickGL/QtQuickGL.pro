TEMPLATE = app

QT += qml quick
#CONFIG += c++11

SOURCES += \
    src/render/window_gl.cpp \
    src/main.cpp \
    src/render/render_engine.cpp \
    src/render/object/drawable.cpp \
    src/io/console.cpp \
    src/render/object/factory.cpp \
    src/render/scene/scene.cpp \
    src/render/scene/test_scene.cpp \
    src/render/object/mesh.cpp \
    src/render/scene/task_scene.cpp \
    src/render/utility/rendertarget.cpp \
    src/render/object/primitive/cvertex.cpp \
    src/render/object/primitive/cedge.cpp \
    src/render/object/primitive/cface.cpp \
    src/render/object/collada.cpp

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
    src/render/object/mesh.h \
    src/render/scene/task_scene.h \
    src/render/utility/rendertarget.h \
    src/render/object/primitive/cvertex.h \
    src/render/object/primitive/cedge.h \
    src/render/object/primitive/cface.h \
    src/render/object/collada.h

OTHER_FILES += \
    rsc/file/*.dat\
    rsc/qml/main.qml \
    rsc/shader/*.frag \
    rsc/shader/*.vert \
    rsc/qml/*.qml \
