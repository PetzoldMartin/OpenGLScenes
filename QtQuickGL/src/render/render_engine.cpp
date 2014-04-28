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

    drawables.push_back(m_factory->GenRectangle(1.0f,1.0f,shader));
}

void RenderEngine::Render()
{
    //iterator i = drawables.begin();
    foreach (Drawable* drawable, drawables) {
        drawable->Draw();
    }
}
