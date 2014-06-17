#ifndef MESH_H
#define MESH_H

class QOpenGLVertexArrayObject;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QObject;

///
/// \brief The Mesh class represents the Geometry Data for an Drawable on the GPU
/// \author André Furchner
///
class Mesh
{
public:

    ///
    /// \brief Create a new Mesh
    ///
    Mesh();

    ///
    /// \brief Delete the Mesh and free the memory on GPU
    ///
    ~Mesh();

    /// \brief BuildVAO Connect the VertexBuffers to an VertexArrayObject
    /// \param context OpenGL Context
    /// \param shader Used Shader
    void BuildVAO(QObject *context, QOpenGLShaderProgram *shader);

    ///
    /// \brief Draw the Mesh
    ///
    void Draw();

    ///
    /// \brief SetVertices Used to upload the Vertex Positions to GPU
    /// \param vertices Vertex Position Data
    /// \param count VertexCount
    ///
    void SetVertices(void *vertices, int count);

    ///
    /// \brief SetNormals Used to upload the Vertex Normals to GPU
    /// \param normals Vertex Normal Data
    /// \param count
    ///
    void SetNormals(void *normals, int count);

private:

    QOpenGLVertexArrayObject *m_vao;    ///< Vertex to Shader Group
    QOpenGLBuffer *m_positionBuffer;    ///< GPU Buffer for Vertex Positions
    QOpenGLBuffer *m_normalBuffer;      ///< GPU Buffer for Vertex Normals

    int m_vertexCount;                  ///< Number of Vertices

    ///
    /// \brief writeBuffer Uploads the data to GPUs Memory
    /// \param buffer The Buffer to Load on
    /// \param data   The Data that will be uploaded
    /// \param size  Size in Bytes
    ///
    void writeBuffer(QOpenGLBuffer *buffer, void* data, int size);
};

#endif // MESH_H
