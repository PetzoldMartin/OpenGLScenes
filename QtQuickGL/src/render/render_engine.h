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

    /// \brief Render all Drawables
    void Render();

    void Update();

    void Resize(float w, float height);
    QOpenGLShaderProgram* GetShader(QString name);

    void AddDrawable(Drawable *drawable);

    //global
    void rotateView(int x,int y);
    void scaleView (int distance);

    //object
    int pickObjectAt(int x, int y);
    void rotateObject(int id,int dx,int dy);

    QObject *GetContext();
private:
    QObject* m_parent;
    Scene *m_scene;
    std::list<Drawable*> drawables;
    std::map<QString, QOpenGLShaderProgram*> m_shaders;
    QMatrix4x4* m_projM;
    float timer;
    float tinv;

    double alpha;
    double beta;
    double distance;

};

#endif // RENDER_ENGINE_H
