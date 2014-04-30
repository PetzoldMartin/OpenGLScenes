#include "factory.h"

#include "src/render/object/drawable.h"

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QVector2D>
#include <QVector4D>
#include <QDataStream>

Factory::Factory(QObject *parent)
{
    m_parent = parent;
    createBasicRectange();
}

Drawable* Factory::GenRectangle(float width, float height, QVector4D color, QOpenGLShaderProgram *shader) {

    QVector2D vert[4];
    QVector4D colors[4];
    unsigned int indi[4];

    colors[0] = color;
    colors[1] = color;
    colors[2] = color;
    colors[3] = color;

    vert[0] = QVector2D(+0.5,+0.5);
    vert[1] = QVector2D(-0.5,+0.5);
    vert[2] = QVector2D(-0.5,-0.5);
    vert[3] = QVector2D(+0.5,-0.5);

    indi[0] = 0;
    indi[1] = 1;
    indi[2] = 2;
    indi[3] = 3;

    QMatrix4x4 *modelMatrix = new QMatrix4x4();
    modelMatrix->setToIdentity();
    modelMatrix->scale(width, height);

    Drawable *rect = new Drawable(m_parent);

    rect->SetVertices(vert,8);
    rect->SetIndices(indi,4);
    rect->SetColors(colors,16);
    rect->SetModelMatrix(modelMatrix);
    rect->SetShader(shader);
    rect->Build();

    return rect;
}


void Factory::createBasicRectange() {

}
