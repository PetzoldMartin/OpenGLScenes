#include "factory.h"

#include "src/render/object/drawable.h"

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QDataStream>

Factory::Factory(QObject *parent)
{
    m_parent = parent;
    createBasicRectange();
}

Drawable* Factory::GenRectangle(float width, float height, QOpenGLShaderProgram *shader) {

    float* vert = new float[8];
    QVector4D colors[4];
    colors[0] = QVector4D(1.0, 0.25, 0.0, 1.0);
    colors[1] = QVector4D(0.0, 0.75, 1.0, 1.0);
    colors[2] = QVector4D(0.75, 1.0, 0.0, 1.0);
    colors[3] = QVector4D(0.75, 0.00, 1.0, 1.0);

    int i = -1;

    vert[++i] = +0.5;
    vert[++i] = +0.5;
    vert[++i] = -0.5;
    vert[++i] = +0.5;
    vert[++i] = -0.5;
    vert[++i] = -0.5;
    vert[++i] = +0.5;
    vert[++i] = -0.5;

    unsigned int* indi = new unsigned int[4];
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
