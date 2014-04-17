#include "drawable.h"

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

void Drawable::SetVertices(float *vertices, int count)
{
    m_vertexBuffer->bind();
    m_vertexBuffer->write(0, vertices, count);
    m_vertexBuffer->release();
}

void Drawable::SetColors(float *colors, int size_t)
{

}

void Drawable::SetIndices(int *indices, int size_t)
{

}
