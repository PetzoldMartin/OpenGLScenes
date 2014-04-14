#include "window_gl.h"


void WindowGL::OnafterRendering()
{

}

void WindowGL::OnsceneGraphInitialized()
{


}

void WindowGL::OnBeforeQt()
{
    fbo = new QOpenGLFramebufferObject(720,576,QOpenGLFramebufferObject::CombinedDepthStencil, GL_TEXTURE_2D,GL_RGBA8);
    setRenderTarget(fbo);

    glColor3d(1.0,0.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex2d(0.5,1.0);
    glVertex2d(-0.5,0.0);
    glVertex2d(0.5,0.0);

    glEnd();
}
