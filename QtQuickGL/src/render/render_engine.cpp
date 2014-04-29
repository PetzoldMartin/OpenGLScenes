#include "render_engine.h"
#include "src/render/object/drawable.h"
#include "src/render/object/factory.h"

#include <iostream>
#include <QForeachContainer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

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

    drawables.push_back(m_factory->GenRectangle(1.0f,1.0f,shader));

    // init gl stuff
    glClearColor(0.0f,0.0f,0.0f,0.0f);
}

void RenderEngine::Render(float width, float height)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set projection matrix
    //TODO: this can be made in a window has changed method
    m_projM->setToIdentity();
    m_projM->scale(height / width, 1.0f, 1.0f);

    shader->bind();
    shader->setUniformValue("projMatrix", *m_projM);
    shader->release();
    ///////////////////////////////////////////////////////

    // Draw all Drawables
    foreach (Drawable* drawable, drawables) {
        drawable->Draw();
    }
}
