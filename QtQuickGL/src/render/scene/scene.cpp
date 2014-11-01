#include "scene.h"
#include "src/render/object/factory.h"
#include "src/render/object/drawable.h"
#include "src/render/render_engine.h"

#include <QMatrix4x4>

Scene::Scene(RenderEngine *engine)
{
    m_engine = engine;
    m_factory = new Factory(m_engine);
    m_lightSource = m_factory->GenCollada("sphere", QVector3D(1,1,1),QVector4D(1,1,1,1));
}

void Scene::Draw() {
    QMatrix4x4 world;
    m_lightSource->Draw(&world); // display light source
    foreach (Drawable *d, m_objects) {
        d->Draw(&world);
    }
}

void Scene::SetLightSourceMatrix(QMatrix4x4 lightMatrix) {
    m_lightSource->SetTransformMatrix(lightMatrix);
}

Drawable* Scene::GetLightSource() {
    return m_lightSource;
}

void Scene::CreateBlock()
{
    m_objects.push_back(m_factory->GenBlock(QVector3D(50,50,500),QVector4D(1,1,0,1)));
}

void Scene::AddBlock(QVector3D size, QVector3D transform, QVector4D color, Drawable *parent) {
    Drawable *drawable = m_factory->GenBlock(size, color);
    AddDrawable(drawable, transform, parent);
}

void Scene::AddSphere(QVector3D size, QVector3D transform, QVector4D color, Drawable *parent)
{
    Drawable *drawable = m_factory->GenCollada("sphere", size, color);
    AddDrawable(drawable, transform, parent);
}

void Scene::AddDrawable(Drawable *drawable, QVector3D transform, Drawable *parent)
{
    QMatrix4x4 trans;
    trans.translate(transform);
    drawable->SetTransformMatrix(trans);
    if(parent != 0) {
        parent->AddChild(drawable,trans);
    } else {
        m_objects.push_back(drawable);
    }
}
