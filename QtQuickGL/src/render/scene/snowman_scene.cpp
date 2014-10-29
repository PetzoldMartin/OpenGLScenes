#include "snowman_scene.h"

#include "src/render/render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/object/factory.h"

#include <QString>
#include <cmath>

SnowmanScene::SnowmanScene(RenderEngine *engine)
    : Scene(engine)
{
    // light
    QMatrix4x4 lightPosition;
    lightPosition.setToIdentity();
    lightPosition.translate(+100,-100,100);
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
        int cole_size= 3;
        int nose_size= 10;

        QVector4D color_snow = QVector4D(1.0,1.0,1.0,1.0);
        QVector4D color_hat = QVector4D(0.0,0.0,0.0,1.0);
        QVector4D color_cole = QVector4D(0.0,0.0,0.0,1.0);
        QVector4D color_carrot = QVector4D(1.0,0.55,0.0,1.0);

    // body
    m_DownSphere = m_factory->GenSphere(QVector3D(dsize,dsize,dsize),color_snow);
    QMatrix4x4 m_dsphere;
    m_dsphere.setToIdentity();
    m_dsphere.translate(QVector3D(0.0,0.0,dsize/2));
    ground->AddChild(m_DownSphere,m_dsphere);

    m_MiddleSphere = m_factory->GenSphere(QVector3D(msize,msize,msize),color_snow);
    QMatrix4x4 m_msphere;
    m_msphere.setToIdentity();
    m_msphere.translate(QVector3D(0.0,0.0,msize));
    m_DownSphere->AddChild(m_MiddleSphere,m_msphere);

    m_TopSphere = m_factory->GenSphere(QVector3D(tsize,tsize,tsize),color_snow);
    QMatrix4x4 m_tsphere;
    m_tsphere.setToIdentity();
    m_tsphere.translate(QVector3D(0.0,0.0,tsize));
    m_MiddleSphere->AddChild(m_TopSphere,m_tsphere);

    // hat
    m_Hat = m_factory->GenCollada("cylinder", QVector3D(tsize,tsize,tsize/2),color_hat);
    QMatrix4x4 mat_hat;
    mat_hat.setToIdentity();
    mat_hat.translate(0,0,tsize/2);
    m_TopSphere->AddChild(m_Hat,mat_hat);

    Drawable * m_hat_brim = m_factory->GenCollada("cylinder", QVector3D(tsize*1.5,tsize*1.5,tsize/8),color_hat);
    QMatrix4x4 mat_hat_brim;
    mat_hat_brim.setToIdentity();
    mat_hat_brim.translate(0,0,-tsize/4);
    m_Hat->AddChild(m_hat_brim,mat_hat_brim);

    // eye
    Drawable *l_eye = m_factory->GenSphere(QVector3D(cole_size,cole_size,cole_size),color_cole);
    QMatrix4x4 m_l_eye;
    m_l_eye.setToIdentity();
    m_l_eye.translate(QVector3D(-tsize/6,-tsize/2,tsize/8));
    m_TopSphere->AddChild(l_eye,m_l_eye);

    Drawable *r_eye = m_factory->GenSphere(QVector3D(cole_size,cole_size,cole_size),color_cole);
    QMatrix4x4 m_r_eye;
    m_r_eye.setToIdentity();
    m_r_eye.translate(QVector3D(+tsize/6,-tsize/2,tsize/8));
    m_TopSphere->AddChild(r_eye,m_r_eye);

    // mouth
    m_Mouth = m_factory->GenSphere(QVector3D(cole_size,cole_size,cole_size),color_cole);
    QMatrix4x4 m_mouth;
    m_mouth.setToIdentity();
    m_mouth.translate(QVector3D(0.0,-tsize/2,-tsize/6));
    m_TopSphere->AddChild(m_Mouth,m_mouth);

    Drawable *mouthl1 = m_factory->GenSphere(QVector3D(cole_size*2/3,cole_size*2/3,cole_size*2/3),color_cole);
    QMatrix4x4 m_mouthl1;
    m_mouthl1.setToIdentity();
    m_mouthl1.translate(QVector3D(-cole_size*1.2,0.5,0));
    m_Mouth->AddChild(mouthl1,m_mouthl1);

    Drawable *mouthl2 = m_factory->GenSphere(QVector3D(cole_size*1/2,cole_size*1/2,cole_size*1/2),color_cole);
    QMatrix4x4 m_mouthl2;
    m_mouthl2.setToIdentity();
    m_mouthl2.translate(QVector3D(-cole_size*0.8,1,0));
    mouthl1->AddChild(mouthl2,m_mouthl2);

    Drawable *mouthr1 = m_factory->GenSphere(QVector3D(cole_size*2/3,cole_size*2/3,cole_size*2/3),color_cole);
    QMatrix4x4 m_mouthr1;
    m_mouthr1.setToIdentity();
    m_mouthr1.translate(QVector3D(+cole_size*1.2,0.5,0));
    m_Mouth->AddChild(mouthr1,m_mouthr1);

    Drawable *mouthr2 = m_factory->GenSphere(QVector3D(cole_size*1/2,cole_size*1/2,cole_size*1/2),color_cole);
    QMatrix4x4 m_mouthr2;
    m_mouthr2.setToIdentity();
    m_mouthr2.translate(QVector3D(+cole_size*0.8,1,0));
    mouthr1->AddChild(mouthr2,m_mouthr2);

    // nose
    m_Nose = m_factory->GenCollada("cone",QVector3D(nose_size/3,nose_size/3,nose_size),color_carrot);
    QMatrix4x4 m_nose;
    m_nose.setToIdentity();
    m_nose.translate(0,-tsize*2/3,0);
    m_nose.rotate(90,QVector3D(1,0,0));
    m_TopSphere->AddChild(m_Nose,m_nose);

    }
    m_objects.push_back(ground);
}

void SnowmanScene::Update()
{
    static int i=15;
    int c =(i%60>=30 ? 1 : -1);
    QVector3D change = QVector3D(0,-0.02*c,0.05 * c);
    foreach(Drawable* child , m_Mouth->m_childList) {
        foreach (Drawable* child2, child->m_childList) {
            child2->TranslateRelative(change*2);
        }
        child->TranslateRelative(change);
    }
    i++;
}
