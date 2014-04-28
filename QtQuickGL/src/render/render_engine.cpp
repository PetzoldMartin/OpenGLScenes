#include "render_engine.h"
#include "src/render/object/drawable.h"

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


    float* vert = new float[8];
    int i = -1;

    vert[++i] = +1.0;
    vert[++i] = +1.0;
    vert[++i] = -1.0;
    vert[++i] = +1.0;
    vert[++i] = -1.0;
    vert[++i] = -1.0;
    vert[++i] = +1.0;
    vert[++i] = -1.0;

    unsigned int* indi = new unsigned int[4];
    indi[0] = 0;
    indi[1] = 1;
    indi[2] = 2;
    indi[3] = 3;

    QMatrix4x4 *modelMatrix = new QMatrix4x4();
    modelMatrix->setToIdentity();
    modelMatrix->scale(1.0f);

    Drawable* d = new Drawable(parent);
    d->SetVertices(vert,8);
    d->SetIndices(indi,4);
    d->SetShader(shader);
    d->SetModelMatrix(modelMatrix);
    d->Build();

    drawables.push_back(d);
}

void RenderEngine::Render()
{
    //iterator i = drawables.begin();
    foreach (Drawable* drawable, drawables) {
        drawable->Draw();
    }
}
