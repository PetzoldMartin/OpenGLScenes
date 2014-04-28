#include "drawable.h"
#include "src/io/console.h"

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>



Drawable::Drawable(QObject* parent)
{
    m_shader = NULL;
    m_vertexBuffer = NULL;
    m_colorBuffer = NULL;
    m_indexBuffer = NULL;
    m_modelMatrix = NULL;
    m_indexCount = 0;
    m_parent = parent;
    m_isValid = false;


}

void Drawable::Draw()
{
    m_shader->bind();
    m_vao->bind();
    m_indexBuffer->bind();

    m_shader->setUniformValue("modelMatrix", *m_modelMatrix);

    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);
    //glDrawArrays(GL_QUADS, 0, 4);
    m_indexBuffer->release();
    m_vao->release();

    m_shader->release();
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

    m_vao = new QOpenGLVertexArrayObject(m_parent);
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
    m_isValid = true;
}

void Drawable::SetVertices(float *vertices, int count)
{
    // Create a VertexBuffer if it is the first Time
    if(m_vertexBuffer == NULL) {
        m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_vertexBuffer->create();
    }
    writeBuffer(m_vertexBuffer, vertices, sizeof(float) * count);
}

void Drawable::SetColors(float *colors, int count)
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

Drawable* Drawable::Duplicate() {
    if(m_isValid) {
    Drawable* d = new Drawable(m_parent);
        d->m_colorBuffer = m_colorBuffer;
        d->m_indexBuffer = m_indexBuffer;
        d->m_indexCount = m_indexCount;
        d->m_modelMatrix = m_modelMatrix;
        d->m_shader = m_shader;
        d->m_vao = m_vao;
        return d;
    } else {
        Console::WriteError("Tryed to Duplicating an unvalid Drawable! Returning NULL!");
        return NULL;
    }
}

void Drawable::writeBuffer(QOpenGLBuffer* buffer, void *data, int count)
{
    buffer->bind();
    buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer->allocate(data, count);
    buffer->release();
}
