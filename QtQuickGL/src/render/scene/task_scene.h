#ifndef TASK_SCENE_H
#define TASK_SCENE_H

#include "src/render/scene/scene.h"

class TaskScene : public Scene
{
public:
    TaskScene(RenderEngine *engine);
    void Create();
    void Update();
    void Draw();

private:
    Drawable *m_gestell, *m_klotz,
    *m_schlitten, *m_vsp, *m_punkt,
    *m_hl, *m_block1, *m_block2;
};

#endif // TASK_SCENE_H
