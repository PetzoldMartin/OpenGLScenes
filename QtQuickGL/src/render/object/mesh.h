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
    ~Mesh();
    void Build(QObject *context, QOpenGLShaderProgram *shader);
    void Draw();

    void SetVertices(void *vertices, int count);
    void SetNormals(void *normals, int count);

private:

    QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_normalBuffer;

    int m_vertexCount;

    void writeBuffer(QOpenGLBuffer *buffer, void* data, int count);
};

#endif // MESH_H
