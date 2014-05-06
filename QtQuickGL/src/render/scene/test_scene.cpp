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


    for(int i = 0; i < 500; ++i) {
        float r = (float)(qrand() % 255) / 255;
        float g = (float)(qrand() % 255) / 255;
        float b = (float)(qrand() % 255) / 255;


        childs.push_back(m_factory->GenRectangle(10.0f,10.0f,QVector4D(r,g,b,1.0),m_engine->GetShader(QString("basic"))));
        QMatrix4x4 *q = new QMatrix4x4();
        q->setToIdentity();
        q->rotate((float)i * 360.0 / 10.0,0.0f,0.0f,1.0f);
        q->translate(20.0f, 0.0f);
        q->scale((r+g+b)*0.5f);

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
    m_d1->GetTransformMatrix()->rotate(20.0f,0.0f,0.0f,1.0f);

    for(int i = 0; i < 500; ++i) {
        float t = (float)(qrand() % 1000) / 1000.0f;
        t -= 0.5f;
        childs[i]->GetTransformMatrix()->rotate(-10.0f,0.0f,0.0f,10.0f);
        childs[i]->GetTransformMatrix()->translate(t,0.0f,0.0f);
        childs[i]->GetTransformMatrix()->scale(1.0f + t*0.01f);
    }
}


