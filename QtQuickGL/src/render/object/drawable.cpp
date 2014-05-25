#include "drawable.h"
#include "src/io/console.h"
#include "src/render/render_engine.h"
#include "src/render/object/mesh.h"

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>


Drawable::Drawable(RenderEngine *engine, QMatrix4x4 *transform)
{
    m_shader = NULL;
    m_mesh = NULL;
    m_modelMatrix = NULL;
    m_engine = engine;
    m_transMatrix = transform;
}

void Drawable::Draw(QMatrix4x4 *transform)
{
    // bind my shader to be used
    m_shader->bind();

    // set my uniform color
    m_shader->setUniformValue("color", m_color);

    // calculate and set uniform variable modelMatrix
    QMatrix4x4 t2 = *transform * *m_transMatrix;
    m_shader->setUniformValue("modelMatrix", t2 * *m_modelMatrix);

    // draw myself
    m_mesh->Draw();
    m_shader->release();

    // draw my childs
    for(unsigned int i = 0; i < m_childList.size(); ++i) {
        m_childList[i]->Draw(&t2);
    }
}

void Drawable::Build()
{
    // first check for wrong usage
    if(m_shader == NULL) {
        Console::WriteError("No Shader assigned for this Drawable!");
        return;
    }

    if(m_mesh == NULL) {
        Console::WriteError("No Mesh is assigned to this Drawable!");
        return;
    }

    if(m_modelMatrix == NULL) {
        Console::WriteError("No ModelMatrix is assigned to this Drawable!");
        return;
    }

    // set uniform variable
    m_shader->setUniformValue("modelMatrix", *m_modelMatrix);
    m_mesh->BuildVAO(m_engine->GetContext(), m_shader);

}

void Drawable::SetMesh(Mesh *mesh)
{
    m_mesh = mesh;
}

void Drawable::SetShader(QOpenGLShaderProgram *shader)
{
    m_shader = shader;
}

void Drawable::SetModelMatrix(QMatrix4x4 *matrix)
{
    m_modelMatrix = matrix;
}

void Drawable::SetTransformMatrix(QMatrix4x4 *matrix)
{
    m_transMatrix = matrix;
}

void Drawable::AddChild(Drawable *child, QMatrix4x4 *transform)
{
    child->m_transMatrix = transform;
    m_childList.push_back(child);
}

void Drawable::SetColor(QVector4D color)
{
    m_color = color;
}

Drawable *Drawable::GetChild(int index)
{
    return m_childList[index];
}

int Drawable::GetChildCount()
{
    return m_childList.size();
}

QMatrix4x4 *Drawable::GetTransformMatrix()
{
    return m_transMatrix;
}
