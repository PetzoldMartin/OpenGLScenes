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
    m_scene = new TaskScene(this);
    timer = 0.5f;
    tinv = 1.0f;
    m_viewMode = 0;

    alpha=0;
    beta=0;
    distance=0.5;

    m_scene->Create();


}

void RenderEngine::Resize(float width, float height) {
    m_projM.setToIdentity();
    m_projM.perspective(90.0f, width / height, 0.1f, 5000.0f);

    QMatrix4x4 view;
    view.setToIdentity();
    view.translate(0.0f,-100.0f,-200.f);
    view.rotate(alpha,0, 1,0);
    view.rotate(beta, 1, 0, 0);

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
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);

    // apply uniform to shader
    QOpenGLShaderProgram* shader = GetShader("basic");
    shader->bind();
    shader->setUniformValue("projMatrix", m_projM);
    shader->setUniformValue("viewMode", m_viewMode);
    shader->release();


    // Draw all Drawables
    QMatrix4x4 world;
    world.setToIdentity();
    foreach (Drawable* drawable, drawables) {
        drawable->Draw(&world);
    }
}

void RenderEngine::Update()
{
    m_scene->Update();
}

void RenderEngine::AddDrawable(Drawable* drawable) {
    drawables.push_back(drawable);
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
        distance *= 1.1;
    } else if (delta > 0) {
        distance *= 0.9;
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
