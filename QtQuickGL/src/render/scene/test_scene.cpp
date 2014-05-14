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
    m_d1 = m_factory->GenRectangle(10.0f,10.0f,QVector4D(1.0,1.0,1.0,1.0),m_engine->GetShader(QString("basic")));


    for(int i = 0; i < 10; ++i) {
        float r = (float)(qrand() % 255) / 255;
        float g = (float)(qrand() % 255) / 255;
        float b = (float)(qrand() % 255) / 255;

        Drawable* d2 = m_factory->GenRectangle(7.5f,7.5f,QVector4D(r,g,b,1.0),m_engine->GetShader(QString("basic")));

        QMatrix4x4 *m1 = new QMatrix4x4();
        m1->setToIdentity();
        m1->rotate((float)i * 360.0 / 10.0,0.0f,0.0f,1.0f);
        m1->translate(20.0f, 0.0f);
        m_d1->AddChild(d2,m1);
        for(int j = 0; j < 5; ++j) {
            Drawable* d3 = m_factory->GenRectangle(2.5f,2.5f,QVector4D(r,g,b,1.0),m_engine->GetShader(QString("basic")));
            QMatrix4x4 *m2 = new QMatrix4x4();
            m2->setToIdentity();
            m2->rotate((float)j * 360.0 / 5.0,0.0f,0.0f,1.0f);
            m2->translate(10.0f, 0.0f);
            d2->AddChild(d3,m2);
        }
    }

    m_engine->AddDrawable(m_d1);
}

void TestScene::Draw()
{
    // TOTO: Need this?
}

void TestScene::Update()
{
    m_d1->GetTransformMatrix()->rotate(-2.0f,0.0f,0.0f,1.0f);


    int counti = m_d1->GetChildCount();
    for(int i = 0; i < counti; ++i) {
       m_d1->GetChild(i)->GetTransformMatrix()->rotate(-2.0f,0.0f,0.0f,10.0f);

       int countj = m_d1->GetChild(i)->GetChildCount();
       for(int j = 0; j < countj; ++j) {
           m_d1->GetChild(i)->GetChild(j)->GetTransformMatrix()->rotate(-2.0f,0.0f,0.0f,10.0f);
       }
    }
}

