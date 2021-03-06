#ifndef RENDER_ENGINE_H
#define RENDER_ENGINE_H

#include <list>
#include <map>
#include <QString>
#include <QMatrix4x4>
#include "object/drawable.h"

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
    void Render(bool isDrawID);

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
    void setMousePose(int x, int y);
    void toggleRenderMode();

    //object
    int pickObjectAt();
    void rotateObject(int deltax,int deltay,int deltaz);
    void translateObject(int dx,int dy,int dz);
    void scaleObject(float factor);
    void forceModification();
    void deselect();
    void CreateBlock(QVector3D size, QVector3D transform);
    void CreateBlock(QVector3D size, QVector3D transform, QVector4D color);
    void CreateSphere(QVector3D size, QVector3D transform, QVector4D color);

    void setFoV(double value) {foV= value;};
    void setNearClipping(double value) {nearClipping=value;};
    void setFarClipping(double value) {farClipping=value;};

    QObject *GetContext();
private:

    bool ortho;
    QObject* m_parent;                                      /// GUI Parent
    std::list<Scene*> m_scenes;                             /// Senes to Draw and Update
    Scene *m_sceneEdit;                                     /// Active Scene Edit
    std::map<QString, QOpenGLShaderProgram*> m_shaders;     /// Shader Container

    //TODO: Camera Class ////
    //TODO: One ore more Cameras can be part of Scenes
    QMatrix4x4 projectionMatrix,viewMatrix,cameraTransformation;


    int height;
    int width;

    double alpha;
    double beta;
    double distance;
    int m_viewMode;

    double foV;
    double farClipping;
    double nearClipping;
    // Camera Class /////////

    int m_mouseX;
    int m_mouseY;
    //QMatrix4x4 lightPosition,lightPositionBack;
    QVector4D m_hoverObjectID;
    Drawable* selectedObject;

};

#endif // RENDER_ENGINE_H
