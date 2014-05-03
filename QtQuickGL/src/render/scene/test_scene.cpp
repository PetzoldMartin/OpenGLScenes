#include "test_scene.h"
#include "src/render/render_engine.h"
#include "src/render/object/factory.h"
#include "src/render/object/drawable.h"

#include <QVector4D>
#include <QMatrix4x4>

TestScene::TestScene(RenderEngine *engine) : Scene(engine)
{
    m_factory = new Factory(m_engine);
}

void TestScene::Create()
{
    Drawable *draw = m_factory->GenRectangle(10.0f,10.0f,QVector4D(0.25,1.0,0.0,1.0),m_engine->GetShader(QString("basic")));
    Drawable *d = m_factory->GenRectangle(5.0f,5.0f,QVector4D(0.25,0.0,1.0,1.0),m_engine->GetShader(QString("basic")));

    QMatrix4x4 *q = new QMatrix4x4();
    q->setToIdentity();
    q->translate(20.0f, 0.0f);

    draw->AddChild(d,q);

    m_engine->AddDrawable(draw);
}

void TestScene::Draw()
{

}

void TestScene::Update()
{

}


