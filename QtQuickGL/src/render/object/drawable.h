#ifndef DRAWABLE_H
#define DRAWABLE_H

// Forward Declaration
class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QMatrix4x4;
class QObject;

/// \brief The Drawable class
/// \author Andre Furchner
class Drawable
{
public:
    Drawable(QObject *parent);

    void Draw();
    void Build();

    void SetVertices(void *vertices, int count);
    void SetColors(void *colors, int count);
    void SetIndices(unsigned int *indices, int count);
    void SetShader(QOpenGLShaderProgram *shader);
    void SetModelMatrix(QMatrix4x4 *matrix);

private:
    QOpenGLVertexArrayObject *m_vao;

    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_colorBuffer;
    QOpenGLBuffer *m_indexBuffer;

    QOpenGLShaderProgram *m_shader;
    QMatrix4x4 *m_modelMatrix;
    QObject *m_parent;

    short m_indexCount;

    void writeBuffer(QOpenGLBuffer *buffer, void* data, int count);
};

#endif // DRAWABLE_H
