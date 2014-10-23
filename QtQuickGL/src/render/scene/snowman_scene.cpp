#include "snowman_scene.h"

#include "src/render/render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/object/factory.h"

SnowmanScene::SnowmanScene(RenderEngine *engine)
    : Scene(engine)
{

}


void SnowmanScene::Create(){
   m_Ground = m_factory->GenBlock(QVector3D(100,100,5),QVector4D(0.5,0.5,0.5,1));

   {
       m_DownSphere = m_factory->GenSphere(QVector3D(55,55,55),QVector4D(0.9,0.9,0.9,1));
       QMatrix4x4 mdown;
           mdown.setToIdentity();
           mdown.translate(0,0,30);
       m_Ground->AddChild(m_DownSphere,mdown);

   }

   m_objects.push_back(m_Ground);
}

void SnowmanScene::Update()
{
    m_DownSphere->RotateRelative(1,QVector3D(0,0,1));
//    //qDebug() << m_lightSource->GetTransformMatrix().rotate(1,QVector3D(1,1,0));
//    QMatrix4x4 lightM = m_lightSource->GetTransformMatrix();
//    lightM.rotate(1,QVector3D(0,0,1));
//    m_lightSource->SetTransformMatrix(lightM);
//    qDebug() << lightM;
//   // m_lightSource->RotateRelative(1,QVector3D(1,1,0));
}
