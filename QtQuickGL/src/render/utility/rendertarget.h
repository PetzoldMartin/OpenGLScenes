#ifndef RENDERTARGET_H
#define RENDERTARGET_H

// Forward Declarations
class QOpenGLTexture;


///
/// \brief The RenderTarget cam draw OpenGL Graphics into Textures
/// \author André Furchner
///
class RenderTarget
{
public:
    RenderTarget();

    void Create();
    void Bind();
    void Release();

    void AddTexture(QOpenGLTexture *texture, int bindpoint);
};

#endif // RENDERTARGET_H
