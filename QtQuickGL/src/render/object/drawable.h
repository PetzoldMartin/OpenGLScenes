#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class Drawable
{
public:
    Drawable(QObject *parent);

    void Draw();

    void SetVertices(float* vertices, int count);
    void SetColors(float* colors, int size_t);
    void SetIndices(int* indices, int size_t);

private:
    QOpenGLVertexArrayObject* m_vao;

    QOpenGLBuffer* m_vertexBuffer;
    QOpenGLBuffer* m_colorBuffer;
    QOpenGLBuffer* m_indexBuffer;
};

#endif // DRAWABLE_H
