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

Drawable* Factory::GenRectangle(float width, float height, QVector4D color, QOpenGLShaderProgram *shader) {

    QVector3D vert[6];
    QVector4D colors[6];

    colors[0] = color;
    colors[1] = color;
    colors[2] = color;
    colors[3] = color;
    colors[4] = color;
    colors[5] = color;


    vert[0] = QVector3D(+0.5,+0.5, 0.0);
    vert[1] = QVector3D(-0.5,+0.5, 0.0);
    vert[2] = QVector3D(-0.5,-0.5, 0.0);

    vert[3] = QVector3D(+0.5,+0.5, 0.0);
    vert[4] = QVector3D(-0.5,-0.5, 0.0);
    vert[5] = QVector3D(+0.5,-0.5, 0.0);

    QMatrix4x4 *modelMatrix = new QMatrix4x4();
    modelMatrix->setToIdentity();
    modelMatrix->scale(width, height);

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
