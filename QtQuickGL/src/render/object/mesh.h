#ifndef MESH_H
#define MESH_H

class QOpenGLVertexArrayObject;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QObject;

class Mesh
{
public:
    Mesh();
    void Build(QObject *context, QOpenGLShaderProgram *shader);
    void Draw();

    void SetVertices(void *vertices, int count);
    void SetColors(void *colors, int count);

private:

    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_colorBuffer;

    void writeBuffer(QOpenGLBuffer *buffer, void* data, int count);
};

#endif // MESH_H
