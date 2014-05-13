#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <list>
#include <map>
#include <QString>

// Forward Declarations
class Drawable;
class QObject;
class QOpenGLShaderProgram;
class QMatrix4x4;
class Scene;

///
/// \brief The RenderEngine class
/// Draws all Drawables
///
class RenderEngine
{
public:
    RenderEngine(QObject *parent);

    ///
    /// \brief Render all Drawables
    ///
    void Render();

    void Resize(float w, float height);
    QOpenGLShaderProgram* GetShader(QString name);

    void AddDrawable(Drawable *drawable);
    QObject *GetContext();
private:
    QObject* m_parent;
    Scene *m_scene;
    std::list<Drawable*> drawables;
    std::map<QString, QOpenGLShaderProgram*> m_shaders;
    QMatrix4x4* m_projM;
    float timer;
    float tinv;

};

#endif // RENDER_ENGINE_H
