#include "render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/scene/task_scene.h"

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
    m_parent = parent;
    m_projM.setToIdentity();
    tinv = 1.0f;
    m_viewMode = 0;

    alpha=0;
    beta=90;
    distance=-200;
    m_mouseX = 0;
    m_mouseY = 0;

    Scene *scene = new TaskScene(this);
    scene->Create();
    m_scenes.push_back(scene);
    cameraView.setToIdentity();
    cameraView.translate(0,-100,distance);
    cameraView.rotate(-90,1,0,0);
}

void RenderEngine::Resize(float width, float height) {
    m_projM.setToIdentity();
    m_projM.perspective(90.0f, width / height, 1.0f, 5000.0f);

    //QMatrix4x4 view;
//    cameraView.setToIdentity();

}

void RenderEngine::Render(bool isDrawID)
{
    // OpenGL Inits
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // apply uniform to shader
    QOpenGLShaderProgram* shader = GetShader("basic");
    shader->bind();
    shader->setUniformValue("projMatrix",m_projM*cameraView);
    shader->setUniformValue("viewMode", m_viewMode);
    if(isDrawID) shader->setUniformValue("isDrawID", 1.0f);
    else shader->setUniformValue("isDrawID", 0.0f);
    shader->setUniformValue("cameraPosition",cameraView.mapVector(QVector3D(0,0,-1)));
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
   // qDebug() << dx << " \t" << dy ;

    cameraView.rotate(dx,0, 0,1);

    cameraView.rotate(dy, 1, 0, 0);
}

void RenderEngine::scaleView (int delta) {
    cameraVector= cameraView.mapVector(QVector3D(0,0,-1));
    if (delta < 0) {
        cameraView.translate(-cameraVector.normalized()*10);
//        cameraView.translate(0,0,+distance/20);
//        if (distance > -500) {
//            distance *= 1.1;
//        }
    } else if (delta > 0) {
        cameraView.translate(cameraVector.normalized()*10);

//        cameraView.translate(0,0,-distance/20);
//        if (distance < -50) {
//            distance *= 0.9;
//        }
    }
    //cameraView.translate(0.0f,-75.0f,distance);
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
    //TODO
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
