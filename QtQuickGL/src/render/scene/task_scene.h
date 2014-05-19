#ifndef TASK_SCENE_H
#define TASK_SCENE_H

#include "src/render/scene/scene.h"

class task_scene : public Scene
{
public:
    task_scene(RenderEngine *engine);
    void Create();
};

#endif // TASK_SCENE_H
