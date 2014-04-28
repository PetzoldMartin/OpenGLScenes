#include "factory.h"

#include "src/render/object/drawable.h"

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

Factory::Factory(QObject *parent)
{
    m_parent = parent;
}

Drawable* Factory::GenRectangle(float width, float height, QOpenGLShaderProgram *shader) {

}


void Factory::createBasicRectange(QOpenGLShaderProgram *shader) {
    float* vert = new float[8];
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
    modelMatrix->scale(1.0f);

    Drawable* d = new Drawable(m_parent);
    d->SetVertices(vert,8);
    d->SetIndices(indi,4);
    d->SetShader(shader);
    d->SetModelMatrix(modelMatrix);
    d->Build();
}
