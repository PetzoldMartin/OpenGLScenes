#include "drawable.h"
#include "src/io/console.h"

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>



Drawable::Drawable(QObject* parent)
{
    m_shader = NULL;
    m_vertexBuffer = NULL;
    m_colorBuffer = NULL;
    m_indexBuffer = NULL;
    m_indexCount = 0;

    m_vao = new QOpenGLVertexArrayObject(parent);
    m_vao->create();
}

void Drawable::Draw()
{
    m_shader->bind();
    m_vao->bind();
    m_indexBuffer->bind();

    glDrawElements(GL_QUADS, m_indexCount, GL_INT, NULL);
    //glDrawArrays(GL_QUADS, 0, 4);
    m_indexBuffer->release();
    m_vao->release();

    /*
    glBegin(GL_QUADS);
    {
        glVertex2d(1.0,1.0);
        glVertex2d(-1.0,1.0);
        glVertex2d(-1.0,-1.0);
        glVertex2d(1.0,-1.0);
    }
    glEnd();
    */

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


    // Now Build the VertexArrayObject
    m_vao->bind();

    if(m_vertexBuffer != NULL) {
        m_vertexBuffer->bind();
        m_shader->setAttributeBuffer("in_position", GL_FLOAT, 0, 2, 0);
        m_vertexBuffer->release();
    }

    if(m_colorBuffer != NULL) {
        m_colorBuffer->bind();
        m_shader->setAttributeBuffer("in_color", GL_FLOAT, 0, 4, 0);
        m_colorBuffer->release();
    }

    m_indexBuffer->bind();
    // TOTO !?!
    m_indexBuffer->release();

    m_vao->release();
}

void Drawable::SetVertices(float *vertices, int count)
{
    // Create a VertexBuffer if it is the first Time
    if(m_vertexBuffer == NULL) {
        m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_vertexBuffer->create();
    }
    writeBuffer(m_vertexBuffer, vertices, count);
}

void Drawable::SetColors(float *colors, int count)
{
    // Create a ColorBuffer if it is the first Time
    if(m_colorBuffer == NULL) {
        m_colorBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_colorBuffer->create();
    }
    writeBuffer(m_colorBuffer, colors, count);
}

void Drawable::SetIndices(int *indices, int count)
{
    // Create a IndexBuffer if it is the first Time
    if(m_indexBuffer == NULL) {
        m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        m_indexBuffer->create();
    }
    writeBuffer(m_indexBuffer, indices, count);
    m_indexCount = count;
}

void Drawable::SetShader(QOpenGLShaderProgram *shader)
{
    m_shader = shader;
}

void Drawable::writeBuffer(QOpenGLBuffer* buffer, void *data, int count)
{
    buffer->bind();
    buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer->allocate(data, count);
    buffer->release();
}
