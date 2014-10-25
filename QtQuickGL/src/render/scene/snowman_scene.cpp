#include "snowman_scene.h"

#include "src/render/render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/object/factory.h"

#include <QString>

SnowmanScene::SnowmanScene(RenderEngine *engine)
    : Scene(engine)
{

}


void SnowmanScene::Create(){
   Drawable *ground = m_factory->GenBlock(QVector3D(512,512,3),QVector4D(0.9,0.9,0.9,1.0));

   Drawable *test = m_factory->GenCollada("test", QVector3D(64,64,64),QVector4D(1.0,0.0,0.25,1.0));
   QMatrix4x4 mat_test;
   mat_test.setToIdentity();
   mat_test.translate(-32,32,32);
   ground->AddChild(test,mat_test);


   m_objects.push_back(ground);
}

void SnowmanScene::Update()
{

}
