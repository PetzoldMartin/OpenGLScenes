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
    m_objects.push_back(m_factory->GenBlock(QVector3D(50,50,500),QVector4D(1,1,0,1)));
}
