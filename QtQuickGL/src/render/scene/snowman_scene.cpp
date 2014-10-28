#include "snowman_scene.h"

#include "src/render/render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/object/factory.h"

#include <QString>

SnowmanScene::SnowmanScene(RenderEngine *engine)
    : Scene(engine)
{
    // light
    QMatrix4x4 lightPosition;
    lightPosition.setToIdentity();
    lightPosition.translate(-100,-100,100);
    m_lightSource->SetTransformMatrix(lightPosition);
    m_lightSource->forceModification();
}


void SnowmanScene::Create(){
    Drawable *ground = m_factory->GenBlock(QVector3D(512,512,3),QVector4D(0.9,0.9,0.9,1.0));
    {
//   Drawable *test = m_factory->GenCollada("test", QVector3D(64,64,64),QVector4D(1.0,0.0,0.25,1.0));
//   QMatrix4x4 mat_test;
//   mat_test.setToIdentity();
//   mat_test.translate(-32,32,32);
//   ground->AddChild(test,mat_test);
        int dsize= 64;
        int msize= 42;
        int tsize= 26;


    m_DownSphere = m_factory->GenSphere(QVector3D(dsize,dsize,dsize),QVector4D(QVector4D(0.9,0.9,0.9,1.0)));
    QMatrix4x4 m_dsphere;
    m_dsphere.setToIdentity();
    m_dsphere.translate(QVector3D(0.0,0.0,dsize/2));
    ground->AddChild(m_DownSphere,m_dsphere);

    m_MiddleSphere = m_factory->GenSphere(QVector3D(msize,msize,msize),QVector4D(QVector4D(0.9,0.9,0.9,1.0)));
    QMatrix4x4 m_msphere;
    m_msphere.setToIdentity();
    m_msphere.translate(QVector3D(0.0,0.0,msize));
    m_DownSphere->AddChild(m_MiddleSphere,m_msphere);

    m_TopSphere = m_factory->GenSphere(QVector3D(tsize,tsize,tsize),QVector4D(QVector4D(0.9,0.9,0.9,1.0)));
    QMatrix4x4 m_tsphere;
    m_tsphere.setToIdentity();
    m_tsphere.translate(QVector3D(0.0,0.0,tsize));
    m_MiddleSphere->AddChild(m_TopSphere,m_tsphere);

    }
    m_objects.push_back(ground);
}

void SnowmanScene::Update()
{

}
