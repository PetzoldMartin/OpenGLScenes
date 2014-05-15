#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>       // for container drawable
#include <QVector4D>    // for color

// Forward Declaration
class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QMatrix4x4;
class QObject;
class RenderEngine;
class Mesh;

/// \brief The Drawable class
/// \author Andre Furchner
class Drawable
{
public:
    Drawable(RenderEngine *engine, QMatrix4x4 *transform);

    void Draw(QMatrix4x4* transform);
    void Build();

    void SetMesh(Mesh *mesh);
    void SetShader(QOpenGLShaderProgram *shader);
    void SetModelMatrix(QMatrix4x4 *matrix);
    void SetTransformMatrix(QMatrix4x4 *matrix);
    void AddChild(Drawable *child, QMatrix4x4 *transform);
    void SetColor(QVector4D color);
    Drawable *GetChild(int index);
    int GetChildCount();

    QMatrix4x4 *GetTransformMatrix();

private:
    Mesh *m_mesh;
    QVector4D m_color;

    QOpenGLShaderProgram *m_shader;
    RenderEngine *m_engine;

    QMatrix4x4 *m_modelMatrix;
    QMatrix4x4 *m_transMatrix;
    short m_indexCount;

    std::vector<Drawable*> m_container;
    int m_childCount;

};

#endif // DRAWABLE_H
