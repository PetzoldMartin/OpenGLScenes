#include "mesh.h"

#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

Mesh::Mesh()
{
    m_vao = NULL;
    m_normalBuffer = NULL;
    m_vertexBuffer = NULL;
}

void Mesh::Build(QObject *context, QOpenGLShaderProgram *shader)
{
    m_vao = new QOpenGLVertexArrayObject(context);
    m_vao->create();
    m_vao->bind();

    if(m_vertexBuffer != NULL) {
        m_vertexBuffer->bind();
        int in_position = shader->attributeLocation("in_position");
        shader->enableAttributeArray(in_position);
        shader->setAttributeBuffer(in_position, GL_FLOAT, 0, 3, 0);
        m_vertexBuffer->release();
    }

    if(m_normalBuffer != NULL) {
        m_normalBuffer->bind();
        int in_normal = shader->attributeLocation("in_normal");
        shader->enableAttributeArray(in_normal);
        shader->setAttributeBuffer(in_normal, GL_FLOAT, 0, 3, 0);
        m_normalBuffer->release();
    }
    m_vao->release();
}

void Mesh::Draw()
{
    m_vao->bind();
    glDrawArrays(GL_TRIANGLES,0,6);
    m_vao->release();
}

void Mesh::SetVertices(void *vertices, int count)
{
    // Create a VertexBuffer if it is the first Time
    if(m_vertexBuffer == NULL) {
        m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_vertexBuffer->create();
    }
    writeBuffer(m_vertexBuffer, vertices, sizeof(float) * count);
}

void Mesh::SetNormals(void *normals, int count)
{
    // Create a ColorBuffer if it is the first Time
    if(m_normalBuffer == NULL) {
        m_normalBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_normalBuffer->create();
    }
    writeBuffer(m_normalBuffer, normals, sizeof(float) * count);
}

void Mesh::writeBuffer(QOpenGLBuffer *buffer, void *data, int count)
{
    buffer->bind();
    buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer->allocate(data, count);
    buffer->release();
}
