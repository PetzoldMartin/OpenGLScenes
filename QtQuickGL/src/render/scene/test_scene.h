#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "src/render/scene/scene.h"

class TestScene : public Scene
{
public:
    TestScene();

    void Draw();
    void Update();
};

#endif // TEST_SCENE_H
