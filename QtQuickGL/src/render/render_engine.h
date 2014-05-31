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
/// \brief The RenderEngine class draws all Drawables
/// \author André Furchner
/// \author Markus Krummnacker
///
class RenderEngine
{
public:

    ///
    /// \brief Create a new RenderEngine
    /// \param parent QObject GUI Parent
    ///
    RenderEngine(QObject *parent);

    ///
    /// \brief Render all Drawables
    ///
    void Render();

    ///
    /// \brief Update Engine stuff
    ///
    void Update();

    ///
    /// \brief Resize the View
    /// \param w in Pixel
    /// \param height   in Pixel
    ///
    void Resize(float w, float height);

    ///
    /// \brief Returns the Shader Object with that name
    /// if it was not created yet than it will create one
    /// \param name
    /// \return
    ///
    QOpenGLShaderProgram* GetShader(QString name);

    ///
    /// \brief Add a Scene that will be renderd
    /// \param scene The Scene Object to render
    ///
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

    QObject* m_parent;                                      /// GUI Parent
    std::list<Scene*> m_scenes;                             /// Senes to Draw and Update
    std::map<QString, QOpenGLShaderProgram*> m_shaders;     /// Shader Container

    //TODO: Camera Class ////
    //TODO: One ore more Cameras can be part of Scenes
    QMatrix4x4 m_projM;
    float timer;
    float tinv;

    int height;
    int width;

    double alpha;
    double beta;
    double distance;
    int m_viewMode;
    // Camera Class /////////

};

#endif // RENDER_ENGINE_H
