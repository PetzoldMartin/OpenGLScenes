#include "render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/object/factory.h"

#include <iostream>
#include <QForeachContainer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QDateTime>
#include <math.h>

using namespace std;

RenderEngine::RenderEngine(QObject* parent)
{

    // create a shader
    shader = new QOpenGLShaderProgram(parent);
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, QString("data/shader/basic.frag"));
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, QString("data/shader/basic.vert"));
    shader->link();

    m_factory = new Factory(parent);

    m_projM = new QMatrix4x4();
    m_projM->setToIdentity();
    m_projM->scale(480.0f / 320.0f, 1.0f, 1.0f);

    shader->bind();
    shader->setUniformValue("projMatrix", *m_projM);
    shader->release();

    drawables.push_back(m_factory->GenRectangle(2.0f,2.0f,shader));
    timer = 0.5f;
    tinv = 1.0f;
}

void RenderEngine::Resize(float width, float height) {
    // set projection matrix
    m_projM->setToIdentity();
    m_projM->scale(height / width, 1.0f, 1.0f);
}

void RenderEngine::Render()
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->bind();
    shader->setUniformValue("projMatrix", *m_projM);
    shader->setUniformValue("time",timer );
    shader->release();

    // Draw all Drawables
    foreach (Drawable* drawable, drawables) {
        drawable->Draw();
    }
    timer += 0.01 * tinv;
    if(timer > 1.0f || timer < 0.0f)
        tinv *= -1.0;

}
