#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "src/render/scene/scene.h"

class Factory;

class TestScene : public Scene
{
public:
    TestScene(RenderEngine *engine);

    void Update();
    void Create();

private:
    Drawable *m_d1;

};

#endif // TEST_SCENE_H
