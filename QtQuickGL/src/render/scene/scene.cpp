#include "scene.h"
#include "src/render/object/factory.h"
#include "src/render/object/drawable.h"

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
