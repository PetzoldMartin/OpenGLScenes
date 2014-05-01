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

    Drawable *draw = m_factory->GenRectangle(10.0f,10.0f,QVector4D(0.25,1.0,0.0,1.0),shader);
    drawables.push_back(draw);

    Drawable *d = m_factory->GenRectangle(5.0f,5.0f,QVector4D(0.25,0.0,1.0,1.0),shader);

    QMatrix4x4 *q = new QMatrix4x4();
    q->setToIdentity();
    q->translate(20.0f, 0.0f);

    draw->AddChild(d,q);

    timer = 0.5f;
    tinv = 1.0f;
}

void RenderEngine::Resize(float width, float height) {
    // set projection matrix
    m_projM->setToIdentity();
    m_projM->scale(2.0f / width, 2.0f / height, 1.0f);
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
    QMatrix4x4 world;
    world.setToIdentity();
    foreach (Drawable* drawable, drawables) {
        drawable->Draw(&world);
    }
    timer += 0.01 * tinv;
    if(timer > 1.0f || timer < 0.0f)
        tinv *= -1.0;

}
