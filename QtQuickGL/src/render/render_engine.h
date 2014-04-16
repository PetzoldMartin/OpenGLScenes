#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <list>

// Forward Declarations
class Drawable;

///
/// \brief The RenderEngine class
/// Draws all Drawables
///
class RenderEngine
{
public:
    RenderEngine();

    ///
    /// \brief Render all Drawables
    ///
    void Render();

private:
    std::list<Drawable*> drawables;

};

#endif // RENDER_ENGINE_H
