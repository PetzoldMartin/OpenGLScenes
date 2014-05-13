#include "test_scene.h"
#include "src/render/render_engine.h"
#include "src/render/object/factory.h"
#include "src/render/object/drawable.h"

#include <QVector4D>
#include <QMatrix4x4>
#include <QtGlobal>

TestScene::TestScene(RenderEngine *engine) : Scene(engine)
{
    m_factory = new Factory(m_engine);
    m_d1 = NULL;
}

void TestScene::Create()
{
    m_d1 = m_factory->GenRectangle(10.0f,10.0f,QVector4D(0.25,1.0,0.0,1.0),m_engine->GetShader(QString("basic")));


    for(int i = 0; i < 10; ++i) {
        float r = (float)(qrand() % 255) / 255;
        float g = (float)(qrand() % 255) / 255;
        float b = (float)(qrand() % 255) / 255;


        childs.push_back(m_factory->GenRectangle(10.0f,10.0f,QVector4D(r,g,b,1.0),m_engine->GetShader(QString("basic"))));
        QMatrix4x4 *q = new QMatrix4x4();
        q->setToIdentity();
        q->rotate((float)i * 360.0 / 10.0,0.0f,0.0f,1.0f);
        q->translate(20.0f, 0.0f);

        m_d1->AddChild(childs[i],q);
    }

    m_engine->AddDrawable(m_d1);
}

void TestScene::Draw()
{
    // TOTO: Need this?
}

void TestScene::Update()
{
    m_d1->GetTransformMatrix()->rotate(2.0f,0.0f,0.0f,1.0f);

    for(int i = 0; i < 10; ++i) {
        childs[i]->GetTransformMatrix()->rotate(-3.0f,0.0f,0.0f,10.0f);
    }
}


