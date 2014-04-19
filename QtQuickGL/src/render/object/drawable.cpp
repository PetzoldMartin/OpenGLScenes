#include "drawable.h"

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

Drawable::Drawable(QObject* parent)
{
    // Create VertexArrayObject
    m_vao = new QOpenGLVertexArrayObject(parent);
    m_vao->create();

    // Create ColorBuffer
    m_colorBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_colorBuffer->create();

    // Create VertexBuffer
    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->create();

    // Create IndexBuffer
    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer->create();
}

void Drawable::Upload()
{
    m_vao->bind();

    m_vertexBuffer->bind();
    //glVertex

    m_vao->release();
}

void Drawable::SetVertices(float *vertices, int count)
{
    writeBuffer(m_vertexBuffer, vertices, count);
}

void Drawable::SetColors(float *colors, int count)
{
    writeBuffer(m_colorBuffer, colors, count);
}

void Drawable::SetIndices(int *indices, int count)
{
    writeBuffer(m_indexBuffer, indices, count);
}

void Drawable::SetShader(QOpenGLShaderProgram *shader)
{
    m_shader = shader;
}

void Drawable::writeBuffer(QOpenGLBuffer* buffer, void *data, int count)
{
    buffer->bind();
    buffer->write(0, data, count);
    buffer->release();
}
