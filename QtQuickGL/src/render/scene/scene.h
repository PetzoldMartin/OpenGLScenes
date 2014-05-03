#ifndef SCENE_H
#define SCENE_H

#include <vector>

class Drawable;
class RenderEngine;

class Scene
{
public:
    Scene(RenderEngine *engine);
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual void Create() = 0;

protected:
    std::vector<Drawable*> m_objects;
    RenderEngine *m_engine;
};

#endif // SCENE_H
