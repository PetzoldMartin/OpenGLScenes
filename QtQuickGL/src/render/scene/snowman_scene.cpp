#include "snowman_scene.h"

#include "src/render/render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/object/factory.h"

SnowmanScene::SnowmanScene(RenderEngine *engine)
    : Scene(engine)
{

}


void SnowmanScene::Create(){
   Drawable *ground = m_factory->GenBlock(QVector3D(50,50,50),QVector4D(1,1,1,1.0));

   m_objects.push_back(ground);


//    // Klotz 50x50
//    m_klotz = m_factory->GenBlock(QVector3D(50,50,50),QVector4D(1.0,0.25,0.0,1.0));
//    QMatrix4x4 mKlotz;
//    mKlotz.setToIdentity();
//    mKlotz.translate(-50,0,55);
//    ground->AddChild(m_klotz,mKlotz);
}

void SnowmanScene::Update()
{

}
