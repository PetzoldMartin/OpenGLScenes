#include "render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/scene/test_scene.h"

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
    m_projM = new QMatrix4x4();
    m_scene = new TestScene(this);
    timer = 0.5f;
    tinv = 1.0f;

    m_scene->Create();
}

void RenderEngine::Resize(float width, float height) {
    // set projection matrix
    m_projM->setToIdentity();
    m_projM->scale(2.0f / width, 2.0f / height, 1.0f);
}

QOpenGLShaderProgram *RenderEngine::GetShader(QString name)
{
    QOpenGLShaderProgram* shader = m_shaders[name];

    // if the shader does not exist create a new
    if(shader == NULL) {
        shader = new QOpenGLShaderProgram(m_parent);
        shader->addShaderFromSourceFile(QOpenGLShader::Fragment, QString("data/shader/" + name + ".frag"));
        shader->addShaderFromSourceFile(QOpenGLShader::Vertex, QString("data/shader/" + name + ".vert"));
        shader->link();
        m_shaders[name] = shader;
    }
    return shader;
}

void RenderEngine::Render()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // apply uniform to shader
    QOpenGLShaderProgram* shader = GetShader("basic");
    shader->bind();
    shader->setUniformValue("projMatrix", *m_projM);
    shader->setUniformValue("time",timer );
    shader->release();


    // Draw all Drawables
    QMatrix4x4 world;
    world.setToIdentity();
    foreach (Drawable* drawable, drawables) {
        drawable->Draw(&world);
    }
    timer += 0.01 * tinv;
    if(timer > 1.0f || timer < 0.0f)
        tinv *= -1.0;

}

void RenderEngine::AddDrawable(Drawable* drawable) {
    drawables.push_back(drawable);
}

QObject *RenderEngine::GetContext()
{
    return m_parent;
}
