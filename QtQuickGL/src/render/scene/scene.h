#ifndef SCENE_H
#define SCENE_H

#include <vector>

class Drawable;

class Scene
{
public:
    Scene();
    virtual void Draw() = 0;
    virtual void Update() = 0;

private:
    std::vector<Drawable*> m_objects;
};

#endif // SCENE_H
