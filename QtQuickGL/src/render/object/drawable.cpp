#include "drawable.h"

Drawable::Drawable(QObject* parent)
{
    m_vao = new QOpenGLVertexArrayObject(parent);
    m_vao->create();

    m_colorBuffer = NULL;
    m_vertexBuffer = NULL;
    m_indexBuffer = NULL;
}

void Drawable::SetVertices(float *vertices, int size_t)
{

}

void Drawable::SetColors(float *colors, int size_t)
{

}

void Drawable::SetIndices(int *indices, int size_t)
{

}
