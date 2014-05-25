#ifndef TASK_SCENE_H
#define TASK_SCENE_H

#include "src/render/scene/scene.h"

///
/// \brief The TaskScene is that scene from Task 1
/// \author André Furchner
///
class TaskScene : public Scene
{
public:

    ///
    /// \brief Create a Scene like that one in Task 1
    /// \param engine The RenderEngine Context
    ///
    TaskScene(RenderEngine *engine);

    ///
    /// \brief Creates the Task 1 Modell
    ///
    void Create();

    ///
    /// \brief Update Drawables
    ///
    void Update();

private:

    /// All Objects from Task 1
    Drawable *m_gestell, *m_klotz,
    *m_schlitten, *m_vsp, *m_punkt,
    *m_hl, *m_block1, *m_block2;
};

#endif // TASK_SCENE_H
