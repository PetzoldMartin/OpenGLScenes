#include "task_scene.h"

#include "src/render/render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/object/factory.h"

TaskScene::TaskScene(RenderEngine *engine)
    : Scene(engine)
{
}

void TaskScene::Create()
{
    QOpenGLShaderProgram* ds =  m_engine->GetShader("basic");

    Drawable *gestell = m_factory->GenBlock(QVector3D(300,100,60),QVector4D(0.5,0.5,0.5,1.0), ds);


    // Klotz 50x50
    Drawable *klotz = m_factory->GenBlock(QVector3D(50,50,50),QVector4D(0.8,0.5,0.5,1.0), ds);
    QMatrix4x4 *mKlotz = new QMatrix4x4();
    mKlotz->setToIdentity();
    mKlotz->translate(-50,0,55);
    gestell->AddChild(klotz,mKlotz);

    // Schlitten 80x40
    Drawable *schlitten = m_factory->GenBlock(QVector3D(80,40,40),QVector4D(0.8,0.8,0.5,1.0), ds);
    QMatrix4x4 *mSchlitten = new QMatrix4x4();
    mSchlitten->setToIdentity();
    mSchlitten->translate(65,0,50);
    gestell->AddChild(schlitten,mSchlitten);

    // Verbindung Schlitten zu Punkt
    Drawable *vsp = m_factory->GenBlock(QVector3D(1,1,150),QVector4D(0.0,0.8,0.5,1.0), ds);
    QMatrix4x4 *mvsp = new QMatrix4x4();
    mvsp->setToIdentity();
    mvsp->translate(0,0,95);
    schlitten->AddChild(vsp,mvsp);

    // Punkt
    Drawable *punkt = m_factory->GenBlock(QVector3D(4,4,4),QVector4D(0.5,0.8,0.8,1.0), ds);
    QMatrix4x4 *mPunkt = new QMatrix4x4();
    mPunkt->setToIdentity();
    mPunkt->translate(0,0,75);
    vsp->AddChild(punkt,mPunkt);

    // H-Linie
    Drawable *hl = m_factory->GenBlock(QVector3D(120,1,1),QVector4D(0.0,0.8,0.5,1.0), ds);
    QMatrix4x4 *mhl = new QMatrix4x4();
    mhl->setToIdentity();
    mhl->translate(0,0,0);
    punkt->AddChild(hl,mhl);

    // Block1
    Drawable *block1 = m_factory->GenBlock(QVector3D(30,30,30),QVector4D(0.8,0.5,0.8,1.0), ds);
    QMatrix4x4 *mBlock1 = new QMatrix4x4();
    mBlock1->setToIdentity();
    mBlock1->translate(-60,0,0);
    mBlock1->rotate(45,0,1,0);
    hl->AddChild(block1,mBlock1);

    // Block2
    Drawable *block2 = m_factory->GenBlock(QVector3D(30,30,30),QVector4D(0.8,0.5,0.8,1.0), ds);
    QMatrix4x4 *mBlock2 = new QMatrix4x4();
    mBlock2->setToIdentity();
    mBlock2->translate(60,0,0);
    hl->AddChild(block2,mBlock2);

    m_engine->AddDrawable(gestell);

}

void TaskScene::Update()
{

}

void TaskScene::Draw()
{

}
