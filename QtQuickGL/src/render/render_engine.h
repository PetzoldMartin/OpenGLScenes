#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <list>
#include <map>
#include <QString>
#include <QMatrix4x4>

// Forward Declarations
class QObject;
class QOpenGLShaderProgram;
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

    void AddScene(Scene *scene);

    //global
    void rotateView(int x,int y);
    void scaleView (int distance);
    void setViewMode(int viewMode);

    //object
    int pickObjectAt(int x, int y);
    void rotateObject(int id,int dx,int dy);

    QObject *GetContext();
private:

    QObject* m_parent;
    std::list<Scene*> m_scenes;
    std::map<QString, QOpenGLShaderProgram*> m_shaders;
    QMatrix4x4 m_projM;
    float timer;
    float tinv;

    int height;
    int width;

    double alpha;
    double beta;
    double distance;
    int m_viewMode;

};

#endif // RENDER_ENGINE_H
