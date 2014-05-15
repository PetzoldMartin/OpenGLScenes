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
}

Drawable* Factory::GenRectangle(QVector3D size,  QVector4D color, QOpenGLShaderProgram *shader) {

    QVector4D colors[] = {
        color,
        color,
        color,

        color,
        color,
        color,
    };

    QVector3D vert[] = {
        QVector3D(+0.5,+0.5, 0.0),
        QVector3D(-0.5,+0.5, 0.0),
        QVector3D(-0.5,-0.5, 0.0),

        QVector3D(+0.5,+0.5, 0.0),
        QVector3D(-0.5,-0.5, 0.0),
        QVector3D(+0.5,-0.5, 0.0),
    };

    QMatrix4x4 *modelMatrix = new QMatrix4x4();
    modelMatrix->setToIdentity();
    modelMatrix->scale(size);

    Mesh *mesh = new Mesh();

    mesh->SetVertices(vert,3*6);
    mesh->SetColors(colors,4*6);

    Drawable *rect = new Drawable(m_engine, new QMatrix4x4());
    rect->SetMesh(mesh);
    rect->SetModelMatrix(modelMatrix);
    rect->SetShader(shader);
    rect->Build();

    return rect;
}
