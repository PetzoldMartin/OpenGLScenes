#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "src/render/scene/scene.h"

class Factory;

class TestScene : public Scene
{
public:
    TestScene(RenderEngine *engine);

    void Draw();
    void Update();
    void Create();

private:
    Factory *m_factory;
};

#endif // TEST_SCENE_H
