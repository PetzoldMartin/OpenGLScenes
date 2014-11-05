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
    Drawable *m_Ground;
    Drawable *m_DownSphere;
    Drawable *m_MiddleSphere;
    Drawable *m_TopSphere;
    Drawable *m_Hat;
    Drawable *m_Nose;
    Drawable *mouthl1;
    Drawable *mouthl2;
    Drawable *mouthr1;
    Drawable *mouthr2;

};

#endif // SNOWMAN_SCENE_H
