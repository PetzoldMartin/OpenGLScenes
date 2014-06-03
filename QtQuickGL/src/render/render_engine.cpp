#include "render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/scene/task_scene.h"
#include "src/render/object/factory.h"

#include <iostream>
#include <QForeachContainer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include <QImage>
#include <QOpenGLContext>
#include <QSurface>
#include <QMatrix4x4>
#include <QDateTime>
#include <math.h>

using namespace std;

RenderEngine::RenderEngine(QObject* parent)
{
    selectedObject=NULL;
    m_parent = parent;
    projectionMatrix.setToIdentity();
    m_viewMode = 0;

    alpha=0;
    beta=90;
    distance=200;
    m_mouseX = 0;
    m_mouseY = 0;

    Scene *scene = new TaskScene(this);
    scene->Create();
    m_scenes.push_back(scene);
    m_sceneEdit = scene;
}

void RenderEngine::Resize(float width, float height) {
    projectionMatrix.setToIdentity();
    if (ortho) {
        float x= width*distance/400.0f;
        projectionMatrix.ortho(-x,x,-x*height / width,x*height / width, 1.0f, 5000.0f);
    } else {
        projectionMatrix.perspective(90.0f, width / height, 1.0f, 5000.0f);
    }
    glViewport(0, 0, width, height);
}

void RenderEngine::Render(bool isDrawID)
{
    // OpenGL Inits
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    QVector3D cameraCenter;
    if (selectedObject!=NULL){
        cameraCenter = selectedObject->GetSceneMatrix()*QVector3D(0,0,0);
    } else {
        cameraCenter= QVector3D(0,0,100);
    }
    QVector3D cameraPosition = cameraTransformation * QVector3D(0, -distance,0 );

    //    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 0, 1);

    viewMatrix.setToIdentity();
    viewMatrix.lookAt(cameraPosition+cameraCenter, cameraCenter, QVector3D(0, 0, 1));

    // apply uniform to shader
    QOpenGLShaderProgram* shader = GetShader("basic");
    shader->bind();
    shader->setUniformValue("projMatrix",projectionMatrix*viewMatrix);
    shader->setUniformValue("viewMode", m_viewMode);
    if(isDrawID) shader->setUniformValue("isDrawID", 1.0f);
    else shader->setUniformValue("isDrawID", 0.0f);
    shader->setUniformValue("cameraPosition",viewMatrix * QVector3D(0,0,-1));
    shader->release();



    // S DIRTY COLOR PICKING ////////////////////////////////////////////////// AREA S //
    if(isDrawID) {
        unsigned char data[4];
        GLint viewport[4];

        // Draw all Scenes
        foreach (Scene* scene, m_scenes) {
            scene->Draw();
        }

        glGetIntegerv(GL_VIEWPORT, viewport);
        glReadPixels(m_mouseX, viewport[3] - m_mouseY, 1, 1, GL_RGB,GL_UNSIGNED_BYTE, &data);
        m_hoverObjectID = QVector4D(data[0] / 255.0, data[1] / 255.0, data[2] / 255.0, data[3] / 255.0);

        Render(false);
    }
    // E DIRTY COLOR PICKING ////////////////////////////////////////////////// AREA E //
    else {

        // Draw all Scenes
        foreach (Scene* scene, m_scenes) {
            scene->Draw();
        }

        // Clean OpenGL Context
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
    }

}

void RenderEngine::Update()
{
    foreach (Scene* scene, m_scenes) {
        scene->Update();
    }
}


//global
void RenderEngine::rotateView(int dx,int dy) {

    //    alpha -= dx%180;
    //    while (alpha < 0) {
    //        alpha += 360;
    //    }
    //    while (alpha >= 360) {
    //        alpha -= 360;
    //    }
    //    beta -= dy%180;
    //    if (beta < 0) {
    //        beta = 0;
    //    }
    //    if (beta > 180) {
    //        beta = 180;
    //    }
    if (!ortho) {
        cameraTransformation.rotate(dx,0, 0, 1);

        cameraTransformation.rotate(dy,1, 0, 0);
    }
}

void RenderEngine::scaleView (int delta) {
    if (delta < 0) {
        if (distance < +500) {
            distance *= 1.1;
        }
    } else if (delta > 0) {
        if (distance > 100) {
            distance *= 0.9;
        }
    }
}

void RenderEngine::setViewMode(int viewMode)
{
    m_viewMode = viewMode;
}

void RenderEngine::setMousePose(int x, int y)
{
    m_mouseX = x;
    m_mouseY = y;
}

void RenderEngine::toggleRenderMode()
{
    if (ortho) {
        ortho=false;
    } else {
        ortho=true;
        cameraTransformation.setToIdentity();
    }
}


// S OBJECTS METHODS ///////////////////////////////////////////////////////////// AREA //


int RenderEngine::pickObjectAt() {
    if (selectedObject != NULL) {
        selectedObject->SetSelected(false);
    }

    selectedObject = Drawable::GetDrawableByID(m_hoverObjectID);
    if (selectedObject != NULL) {
        selectedObject->SetSelected(true);
    } else {
        qDebug() << "nothing to select";
    }
    return 0;
}

void RenderEngine::rotateObject(int id,int dx,int dy) {
    if (selectedObject != NULL) {
        selectedObject->RotateRelative(dx,QVector3D(1.0f,0.0f,0.0f));
    }
}

void RenderEngine::translateObject(int id,int dx,int dy,int dz) {
        if (selectedObject != NULL) {
            selectedObject->TranslateRelative(QVector3D(dx,dy,dz));
        }

}

void RenderEngine::CreateBlock(QVector3D size, QVector3D transform, QVector4D color)
{
    m_sceneEdit->AddBlock(size,transform, color, selectedObject);
}


// S OBJECTS METHODS ///////////////////////////////////////////////////////////// AREA //


QOpenGLShaderProgram *RenderEngine::GetShader(QString name)
{
    QOpenGLShaderProgram* shader = m_shaders[name];

    // if the shader does not exist create a new
    if(shader == NULL) {
        shader = new QOpenGLShaderProgram(m_parent);
        shader->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(":/shader/" + name + ".frag"));
        shader->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(":/shader/" + name + ".vert"));
        shader->link();
        m_shaders[name] = shader;
    }
    return shader;
}

void RenderEngine::AddScene(Scene* scene) {
    m_scenes.push_back(scene);
}

QObject *RenderEngine::GetContext()
{
    return m_parent;
}

