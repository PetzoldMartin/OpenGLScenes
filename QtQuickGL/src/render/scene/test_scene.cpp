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
    m_d1 = m_factory->GenBlock(QVector3D(10.0f,10.0f,10.0f),QVector4D(1.0,1.0,1.0,1.0),m_engine->GetShader(QString("basic")));


    for(int i = 0; i < 10; ++i) {
        float r = (float)(qrand() % 255) / 255;
        float g = (float)(qrand() % 255) / 255;
        float b = (float)(qrand() % 255) / 255;

        Drawable* d2 = m_factory->GenRectangle(QVector3D(7.0f,7.0f,1.0f),QVector4D(r,g,b,1.0),m_engine->GetShader(QString("basic")));

        QMatrix4x4 *m1 = new QMatrix4x4();
        m1->setToIdentity();
        m1->rotate((float)i * 360.0 / 10.0,0.0f,0.0f,1.0f);
        m1->translate(20.0f, 0.0f);
        m_d1->AddChild(d2,m1);
        for(int j = 0; j < 5; ++j) {
            Drawable* d3 = m_factory->GenRectangle(QVector3D(2.0f,2.0f,1.0f),QVector4D(r,g,b,1.0),m_engine->GetShader(QString("basic")));
            QMatrix4x4 *m2 = new QMatrix4x4();
            m2->setToIdentity();
            m2->rotate((float)j * 360.0 / 5.0,0.0f,0.0f,1.0f);
            m2->translate(10.0f, 0.0f,i*10);
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
    // Nothing to do
}


