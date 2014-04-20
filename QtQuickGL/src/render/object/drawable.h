#ifndef DRAWABLE_H
#define DRAWABLE_H

// Forward Declaration
class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QObject;

/// \brief The Drawable class
/// \author Andre Furchner
class Drawable
{
public:
    Drawable(QObject *parent);

    void Draw();
    void Build();

    void SetVertices(float *vertices, int count);
    void SetColors(float *colors, int count);
    void SetIndices(int *indices, int count);
    void SetShader(QOpenGLShaderProgram *shader);

private:
    QOpenGLVertexArrayObject *m_vao;

    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_colorBuffer;
    QOpenGLBuffer *m_indexBuffer;

    QOpenGLShaderProgram *m_shader;

    short m_indexCount;

    void writeBuffer(QOpenGLBuffer *buffer, void* data, int count);
};

#endif // DRAWABLE_H
