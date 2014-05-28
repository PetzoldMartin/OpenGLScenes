#include "task_scene.h"

#include "src/render/render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/object/factory.h"
#include <QTime>
#include <QtMath>

TaskScene::TaskScene(RenderEngine *engine)
    : Scene(engine)
{
}

void TaskScene::Create()
{
    QOpenGLShaderProgram* ds =  m_engine->GetShader("basic");

    m_gestell = m_factory->GenBlock(QVector3D(300,100,60),QVector4D(0.5,0.5,0.5,1.0), ds);


    // Klotz 50x50
    m_klotz = m_factory->GenBlock(QVector3D(50,50,50),QVector4D(0.8,0.5,0.5,1.0), ds);
    QMatrix4x4 *mKlotz = new QMatrix4x4();
    mKlotz->setToIdentity();
    mKlotz->translate(-50,0,55);
    m_gestell->AddChild(m_klotz,mKlotz);

    // Schlitten 80x40
    m_schlitten = m_factory->GenBlock(QVector3D(80,40,40),QVector4D(0.8,0.8,0.5,1.0), ds);
    QMatrix4x4 *mSchlitten = new QMatrix4x4();
    mSchlitten->setToIdentity();
    mSchlitten->translate(65,0,50);
    m_gestell->AddChild(m_schlitten,mSchlitten);

    // Verbindung Schlitten zu Punkt
    m_vsp = m_factory->GenBlock(QVector3D(1,1,150),QVector4D(0.0,0.8,0.5,1.0), ds);
    QMatrix4x4 *mvsp = new QMatrix4x4();
    mvsp->setToIdentity();
    mvsp->translate(0,0,95);
    m_schlitten->AddChild(m_vsp,mvsp);

    // Punkt
    m_punkt = m_factory->GenBlock(QVector3D(4,4,4),QVector4D(0.5,0.8,0.8,1.0), ds);
    QMatrix4x4 *mPunkt = new QMatrix4x4();
    mPunkt->setToIdentity();
    mPunkt->translate(0,0,75);
    m_vsp->AddChild(m_punkt,mPunkt);

    // H-Linie
    m_hl = m_factory->GenBlock(QVector3D(120,1,1),QVector4D(0.0,0.8,0.5,1.0), ds);
    QMatrix4x4 *mhl = new QMatrix4x4();
    mhl->setToIdentity();
    mhl->translate(0,0,0);
    m_punkt->AddChild(m_hl,mhl);

    // Block1
    m_block1 = m_factory->GenBlock(QVector3D(30,30,30),QVector4D(0.8,0.5,0.8,1.0), ds);
    QMatrix4x4 *mBlock1 = new QMatrix4x4();
    mBlock1->setToIdentity();
    mBlock1->translate(-60,0,0);
    mBlock1->rotate(45,0,1,0);
    m_hl->AddChild(m_block1,mBlock1);

    // Block2
    m_block2 = m_factory->GenBlock(QVector3D(30,30,30),QVector4D(0.8,0.5,0.8,1.0), ds);
    QMatrix4x4 *mBlock2 = new QMatrix4x4();
    mBlock2->setToIdentity();
    mBlock2->translate(60,0,0);
    m_hl->AddChild(m_block2,mBlock2);

    m_objects.push_back(m_gestell);

}

void TaskScene::Update()
{
    m_punkt->GetTransformMatrix()->rotate(3,0,1,0);
    m_schlitten->GetTransformMatrix()->translate( qSin(QTime::currentTime().second()*2)*0.9,0,0);
}

