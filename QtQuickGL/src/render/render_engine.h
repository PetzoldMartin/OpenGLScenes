#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <list>
#include <map>
#include <QString>

// Forward Declarations
class Drawable;
class QObject;
class QOpenGLShaderProgram;
class Factory;
class QMatrix4x4;

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
private:
    QObject* m_parent;
    std::list<Drawable*> drawables;
    std::map<QString, QOpenGLShaderProgram*> m_shaders;
    Factory *m_factory;
    QMatrix4x4* m_projM;
    float timer;
    float tinv;

};

#endif // RENDER_ENGINE_H
