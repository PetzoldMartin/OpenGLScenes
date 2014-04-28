#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <list>

// Forward Declarations
class Drawable;
class QObject;
class QOpenGLShaderProgram;
class Factory;

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

private:
    std::list<Drawable*> drawables;
    QOpenGLShaderProgram* shader;
    Factory *m_factory;

};

#endif // RENDER_ENGINE_H
