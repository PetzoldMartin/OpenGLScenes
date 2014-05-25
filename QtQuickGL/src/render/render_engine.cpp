#include "render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/scene/task_scene.h"

#include <iostream>
#include <QForeachContainer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QDateTime>
#include <math.h>

using namespace std;

RenderEngine::RenderEngine(QObject* parent)
{
    m_parent = parent;
    m_projM.setToIdentity();
    timer = 0.5f;
    tinv = 1.0f;
    m_viewMode = 0;

    alpha=0;
    beta=90;
    distance=-200;

    Scene *scene = new TaskScene(this);
    scene->Create();
    m_scenes.push_back(scene);


}

void RenderEngine::Resize(float width, float height) {
    m_projM.setToIdentity();
    m_projM.perspective(90.0f, width / height, 1.0f, 5000.0f);

    QMatrix4x4 view;
    view.setToIdentity();
    view.translate(0.0f,-75.0f,distance);
    view.rotate(-alpha,0, 1,0);
    view.rotate(-beta, 1, 0, 0);

    m_projM = m_projM * view;
}

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

void RenderEngine::Render()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // apply uniform to shader
    QOpenGLShaderProgram* shader = GetShader("basic");
    shader->bind();
    shader->setUniformValue("projMatrix", m_projM);
    shader->setUniformValue("viewMode", m_viewMode);
    shader->release();


    // Draw all Scenes
    foreach (Scene* scene, m_scenes) {
        scene->Draw();
    }

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

}

void RenderEngine::Update()
{
    foreach (Scene* scene, m_scenes) {
        scene->Update();
    }
}

void RenderEngine::AddScene(Scene* scene) {
    m_scenes.push_back(scene);
}

QObject *RenderEngine::GetContext()
{
    return m_parent;
}
//global
void RenderEngine::rotateView(int dx,int dy) {
    alpha -= dx%180;
    while (alpha < 0) {
        alpha += 360;
    }
    while (alpha >= 360) {
        alpha -= 360;
    }
    beta -= dy%180;
    if (beta < -90) {
        beta = -90;
    }
    if (beta > 90) {
        beta = 90;
    }

}

void RenderEngine::scaleView (int delta) {
    if (delta < 0) {
        if (distance > -500) {
            distance *= 1.1;
        }
    } else if (delta > 0) {
        if (distance < -50) {
            distance *= 0.9;
        }
    }
}

void RenderEngine::setViewMode(int viewMode)
{
    m_viewMode = viewMode;
}


//object
int RenderEngine::pickObjectAt(int x, int y) {
    return 0;
}

void RenderEngine::rotateObject(int id,int dx,int dy) {
    //TODO
}
