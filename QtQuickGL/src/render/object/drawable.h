#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>

// Forward Declaration
class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QMatrix4x4;
class QObject;
class RenderEngine;

/// \brief The Drawable class
/// \author Andre Furchner
class Drawable
{
public:
    Drawable(RenderEngine *engine, QMatrix4x4 *transform);

    void Draw(QMatrix4x4* transform);
    void Build();

    void SetVertices(void *vertices, int count);
    void SetColors(void *colors, int count);
    void SetIndices(unsigned int *indices, int count);
    void SetShader(QOpenGLShaderProgram *shader);
    void SetModelMatrix(QMatrix4x4 *matrix);
    void AddChild(Drawable *child, QMatrix4x4 *transform);

private:
    QOpenGLVertexArrayObject *m_vao;

    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_colorBuffer;
    QOpenGLBuffer *m_indexBuffer;

    QOpenGLShaderProgram *m_shader;
    RenderEngine *m_engine;

    QMatrix4x4 *m_modelMatrix;
    QMatrix4x4 *m_transMatrix;
    short m_indexCount;

    std::vector<Drawable*> m_container;

    void writeBuffer(QOpenGLBuffer *buffer, void* data, int count);
};

#endif // DRAWABLE_H
