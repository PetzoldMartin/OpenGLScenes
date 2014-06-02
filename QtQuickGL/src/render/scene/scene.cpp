#include "scene.h"
#include "src/render/object/factory.h"
#include "src/render/object/drawable.h"
#include "src/render/render_engine.h"

#include <QMatrix4x4>

Scene::Scene(RenderEngine *engine)
{
    m_engine = engine;
    m_factory = new Factory(m_engine);
}

void Scene::Draw() {
    QMatrix4x4 world;
    foreach (Drawable *d, m_objects) {
        d->Draw(&world);
    }
}

void Scene::CreateBlock()
{
    m_objects.push_back(m_factory->GenBlock(QVector3D(50,50,500),QVector4D(1,1,0,1), m_engine->GetShader("basic")));
}

void Scene::AddSceneTask(SceneTask task)
{
    m_tasks.enqueue(task);
}

void Scene::Update()
{
    SceneTask c_task;
    while(m_tasks.size() != 0) {
        c_task = m_tasks.dequeue();

        switch (c_task.task) {
        case Task::Create:
            // TODO Create a new Object
            break;
        case Task::Delete:
            // TODO Delete Drawable
            break;
        case Task::Modify:
            // TODO Modify
            break;
        default:
            break;
        }
    }
}
