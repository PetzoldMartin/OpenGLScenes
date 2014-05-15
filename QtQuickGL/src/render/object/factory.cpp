#include "factory.h"

#include "src/render/object/drawable.h"
#include "src/render/render_engine.h"
#include "src/render/object/mesh.h"
#include "src/io/console.h"

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QDataStream>

Factory::Factory(RenderEngine *engine)
{
    m_engine = engine;
    m_rectangle = NULL;
    m_block = NULL;

    createMeshRectangle();
    createMeshBlock();
}

Drawable* Factory::GenRectangle(QVector3D size,  QVector4D color, QOpenGLShaderProgram *shader) {

    QMatrix4x4 *modelMatrix = new QMatrix4x4();
    modelMatrix->setToIdentity();
    modelMatrix->scale(size);

    Drawable *rect = new Drawable(m_engine, new QMatrix4x4());
    rect->SetMesh(m_rectangle);
    rect->SetModelMatrix(modelMatrix);
    rect->SetShader(shader);
    rect->SetColor(color);
    rect->Build();

    return rect;
}

Drawable *Factory::GenBlock(QVector3D size, QVector4D color, QOpenGLShaderProgram *shader)
{

    QMatrix4x4 *modelMatrix = new QMatrix4x4();
    modelMatrix->setToIdentity();
    modelMatrix->scale(size);

    Drawable *block = new Drawable(m_engine, new QMatrix4x4());
    block->SetMesh(m_block);
    block->SetModelMatrix(modelMatrix);
    block->SetShader(shader);
    block->SetColor(color);
    block->Build();

    return block;
}

void Factory::createMeshRectangle()
{
    QVector3D normal[] = {
        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),

        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),
    };

    QVector3D vert[] = {
        QVector3D(+0.5, +0.5, 0.0),
        QVector3D(-0.5, -0.5, 0.0),
        QVector3D(-0.5, +0.5, 0.0),

        QVector3D(+0.5, +0.5, 0.0),
        QVector3D(+0.5, -0.5, 0.0),
        QVector3D(-0.5, -0.5, 0.0),
    };

    m_rectangle = new Mesh();
    m_rectangle->SetVertices(vert,3*6);
    m_rectangle->SetNormals(normal,3*6);
}

void Factory::createMeshBlock()
{
    QVector3D normal[] = {

        // TOP
        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),

        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),


        // BOTOM
        QVector3D(+0.0, +0.0, -1.0),
        QVector3D(+0.0, +0.0, -1.0),
        QVector3D(+0.0, +0.0, -1.0),

        QVector3D(+0.0, +0.0, -1.0),
        QVector3D(+0.0, +0.0, -1.0),
        QVector3D(+0.0, +0.0, -1.0),
    };

    QVector3D vert[] = {

        // TOP
        QVector3D(+0.5, +0.5, +0.5),
        QVector3D(-0.5, +0.5, +0.5),
        QVector3D(-0.5, -0.5, +0.5),

        QVector3D(+0.5, +0.5, +0.5),
        QVector3D(-0.5, -0.5, +0.5),
        QVector3D(+0.5, -0.5, +0.5),


        // BOTOM
        QVector3D(+0.5, +0.5, -0.5),
        QVector3D(-0.5, +0.5, -0.5),
        QVector3D(-0.5, -0.5, -0.5),

        QVector3D(+0.5, +0.5, -0.5),
        QVector3D(-0.5, -0.5, -0.5),
        QVector3D(+0.5, -0.5, -0.5),
    };

    m_block = new Mesh();
    m_block->SetVertices(vert,3*12);
    m_block->SetNormals(normal,3*12);
}
