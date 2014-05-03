#include "drawable.h"
#include "src/io/console.h"
#include "src/render/render_engine.h"

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>


Drawable::Drawable(RenderEngine *engine, QMatrix4x4 *transform)
{
    m_shader = NULL;
    m_vertexBuffer = NULL;
    m_colorBuffer = NULL;
    m_indexBuffer = NULL;
    m_modelMatrix = NULL;
    m_indexCount = 0;
    m_engine = engine;
    m_transMatrix = transform;
}

void Drawable::Draw(QMatrix4x4 *transform)
{
    m_shader->bind();
    m_vao->bind();
    m_indexBuffer->bind();

    QMatrix4x4 t2 = *transform * *m_transMatrix;
    m_shader->setUniformValue("modelMatrix", t2 * *m_modelMatrix);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);
    //glDrawArrays(GL_QUADS, 0, 4);
    m_indexBuffer->release();
    m_vao->release();

    m_shader->release();

    for(unsigned int i = 0; i < m_container.size(); ++i) {
        m_container[i]->Draw(&t2);
    }
}

void Drawable::Build()
{
    // first check for wrong usage
    if(m_shader == NULL) {
        Console::WriteError("No Shader assigned for this Drawable!");
        return;
    }

    if(m_indexBuffer == NULL) {
        Console::WriteError("No Indices are assigned for this Drawable!");
        return;
    }

    if(m_modelMatrix == NULL) {
        Console::WriteError("No ModelMatrix is assigned to this Drawable!");
        return;
    }

    m_vao = new QOpenGLVertexArrayObject(m_engine->GetContext());
    m_vao->create();

    // set uniform variable
    m_shader->setUniformValue("modelMatrix", *m_modelMatrix);

    // Now Build the VertexArrayObject
    m_vao->bind();

    if(m_vertexBuffer != NULL) {
        m_vertexBuffer->bind();
        int in_position = m_shader->attributeLocation("in_position");
        m_shader->enableAttributeArray(in_position);
        m_shader->setAttributeBuffer(in_position, GL_FLOAT, 0, 2, 0);
        m_vertexBuffer->release();
    }

    if(m_colorBuffer != NULL) {
        m_colorBuffer->bind();
        int in_color = m_shader->attributeLocation("in_color");
        m_shader->enableAttributeArray(in_color);
        m_shader->setAttributeBuffer(in_color, GL_FLOAT, 0, 4, 0);
        m_colorBuffer->release();
    }
    m_vao->release();
}

void Drawable::SetVertices(void *vertices, int count)
{
    // Create a VertexBuffer if it is the first Time
    if(m_vertexBuffer == NULL) {
        m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_vertexBuffer->create();
    }
    writeBuffer(m_vertexBuffer, vertices, sizeof(float) * count);
}

void Drawable::SetColors(void *colors, int count)
{
    // Create a ColorBuffer if it is the first Time
    if(m_colorBuffer == NULL) {
        m_colorBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_colorBuffer->create();
    }
    writeBuffer(m_colorBuffer, colors, sizeof(float) * count);
}

void Drawable::SetIndices(unsigned int *indices, int count)
{
    // Create a IndexBuffer if it is the first Time
    if(m_indexBuffer == NULL) {
        m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        m_indexBuffer->create();
    }
    writeBuffer(m_indexBuffer, indices, sizeof(unsigned int) * count);
    m_indexCount = count;
}

void Drawable::SetShader(QOpenGLShaderProgram *shader)
{
    m_shader = shader;
}

void Drawable::SetModelMatrix(QMatrix4x4 *matrix)
{
    m_modelMatrix = matrix;
}

void Drawable::AddChild(Drawable *child, QMatrix4x4 *transform)
{
    child->m_transMatrix = transform;
    m_container.push_back(child);
}

void Drawable::writeBuffer(QOpenGLBuffer* buffer, void *data, int count)
{
    buffer->bind();
    buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer->allocate(data, count);
    buffer->release();
}
