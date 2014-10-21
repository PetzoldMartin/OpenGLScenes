#ifndef SNOWMAN_SCENE_H
#define SNOWMAN_SCENE_H

#include "src/render/scene/scene.h"

class SnowmanScene : public Scene
{
public:
    SnowmanScene(RenderEngine *engine);

    void Update();
    void Create();

private:
    Drawable *m_Snowman;
    Drawable *m_Mouth;
};

#endif // SNOWMAN_SCENE_H
