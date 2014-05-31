#include "mesh.h"

#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

Mesh::Mesh()
{
    m_vao = 0;
    m_normalBuffer = 0;
    m_positionBuffer = 0;
    m_vertexCount = 0;
}

Mesh::~Mesh()
{
    delete m_normalBuffer;
    delete m_positionBuffer;
    delete m_vao;
}

void Mesh::BuildVAO(QObject *context, QOpenGLShaderProgram *shader)
{
    // create and bind a new VertexArrayObject
    m_vao = new QOpenGLVertexArrayObject(context);
    m_vao->create();
    m_vao->bind();

    // setup position buffer
    if(m_positionBuffer != 0) {

        // bind the buffer to the active context
        m_positionBuffer->bind();

        // get the in_position bind index from shader and enable it
        int in_position = shader->attributeLocation("in_position");
        shader->enableAttributeArray(in_position);

        // tell opengl how to use the positionBuffer structure
        shader->setAttributeBuffer(in_position, GL_FLOAT, 0, 3, 0);

        // release the buffer from active context
        m_positionBuffer->release();
    }

    // setup normal buffer
    if(m_normalBuffer != 0) {

        // bind the buffer to the active context
        m_normalBuffer->bind();

        // get the in_normal bind index from shader and enable it
        int in_normal = shader->attributeLocation("in_normal");
        shader->enableAttributeArray(in_normal);

        // tell opengl how to use the normalBuffer structure
        shader->setAttributeBuffer(in_normal, GL_FLOAT, 0, 3, 0);

        // release the buffer from active context
        m_normalBuffer->release();
    }

    // release the VertexArrayObject from active context
    m_vao->release();
}

void Mesh::Draw()
{
    m_vao->bind();
    glDrawArrays(GL_TRIANGLES,0,m_vertexCount);
    m_vao->release();
}

void Mesh::SetVertices(void *vertices, int count)
{
    // Create a VertexBuffer if it is the first Time
    if(m_positionBuffer == 0) {
        m_positionBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_positionBuffer->create();
    }
    writeBuffer(m_positionBuffer, vertices, sizeof(float) * count * 3);
    m_vertexCount = count;
}

void Mesh::SetNormals(void *normals, int count)
{
    // Create a ColorBuffer if it is the first Time
    if(m_normalBuffer == 0) {
        m_normalBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_normalBuffer->create();
    }
    writeBuffer(m_normalBuffer, normals, sizeof(float) * count * 3);
}

void Mesh::writeBuffer(QOpenGLBuffer *buffer, void *data, int size)
{
    buffer->bind();
    buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer->allocate(data, size);
    buffer->release();
}
