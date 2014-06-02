#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QQueue>

class Drawable;
class RenderEngine;
class Factory;

#include <QQuickItem>

namespace Task {
    enum Task_e {
        Create,
        Delete,
        Modify
    };
}

struct SceneTask {
    Drawable *drawable;
    Task::Task_e task;

    float params[8];
};

///
/// \brief The Scene class contains Drawables and manage them
/// \author André Furchner
///
class Scene
{
public:

    ///
    /// \brief Create new Scene
    /// \param engine The RenderEngine Context
    ///
    Scene(RenderEngine *engine);

    ///
    /// \brief Draw the Scene
    ///
    void Draw();

    void CreateBlock();

    void AddSceneTask(SceneTask task);

    virtual void Update();
    virtual void Create() = 0;

protected:
    std::vector<Drawable*> m_objects;           ///< Container for all Objects
    RenderEngine *m_engine;                     ///< RenderEngine Context
    Factory *m_factory;                         ///< Factory to Generate Drawables
    QQueue<SceneTask> m_tasks;
};

#endif // SCENE_H
