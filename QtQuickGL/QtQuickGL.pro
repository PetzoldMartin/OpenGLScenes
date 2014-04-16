TEMPLATE = app

QT += qml quick

SOURCES += \
    src/render/window_gl.cpp \
    src/main.cpp \
    src/render/render_engine.cpp \
    src/render/object/drawable.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/render/window_gl.h \
    src/render/render_engine.h \
    src/render/object/drawable.h

OTHER_FILES += \
    data/shader/basic.frag \
    data/shader/basic.vert

# Copy Files
copydata.commands = $(COPY_DIR) $$PWD/data $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
