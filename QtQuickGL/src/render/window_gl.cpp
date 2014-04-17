#include "window_gl.h"
#include <iostream>
#include <QItemSelectionModel>


using namespace std;

WindowGL::WindowGL()
    : QQuickView()
{


}

void WindowGL::OnafterQt()
{

}

void WindowGL::OnsceneGraphInitialized()
{ 
    cout << "SceneGraphInitialized" << endl;
    fbo_render = new QOpenGLFramebufferObject(200,150,QOpenGLFramebufferObject::CombinedDepthStencil, GL_TEXTURE_2D,GL_RGBA8);
    setRenderTarget(fbo_render);
    shader = new QOpenGLShaderProgram(parent());
    shader->addShaderFromSourceFile(QOpenGLShader::Fragment, QString("data/shader/basic.frag"));
    shader->addShaderFromSourceFile(QOpenGLShader::Vertex, QString("data/shader/basic.vert"));
    shader->link();

    // test
    for(int i = 10; i >= 0; --i) {
        cout << i << endl;
    }

}

void WindowGL::OnBeforeQt()
{

    shader->bind();

    glBegin(GL_TRIANGLES);
    {
        glVertex2d(0.5,1.0);
        glVertex2d(-0.5,0.0);
        glVertex2d(0.5,0.0);
    }
    glEnd();

    shader->release();
}
