#include "scene.h"
#include "src/render/object/factory.h"

Scene::Scene(RenderEngine *engine)
{
    m_engine = engine;
    m_factory = new Factory(m_engine);
}
