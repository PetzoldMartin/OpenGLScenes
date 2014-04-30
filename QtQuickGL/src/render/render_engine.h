#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <list>

// Forward Declarations
class Drawable;
class QObject;
class QOpenGLShaderProgram;
class Factory;
class QMatrix4x4;

///
/// \brief The RenderEngine class
/// Draws all Drawables
///
class RenderEngine
{
public:
    RenderEngine(QObject *parent);

    ///
    /// \brief Render all Drawables
    ///
    void Render();

    void Resize(float w, float height);
private:
    std::list<Drawable*> drawables;
    QOpenGLShaderProgram* shader;
    Factory *m_factory;
    QMatrix4x4* m_projM;
    float timer;
    float tinv;

};

#endif // RENDER_ENGINE_H
