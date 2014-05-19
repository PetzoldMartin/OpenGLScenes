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
};

#endif // TASK_SCENE_H
