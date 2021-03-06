#ifndef SCENE_H
#define SCENE_H

#include <vector>

class Drawable;
class RenderEngine;
class Factory;

#include <QQuickItem>

///
/// \brief The Scene class contains Drawables and manage them
/// \author André Furchner
///
class Scene
{
public:

    ///
    /// \brief Create new Scene
    /// \param engine The RenderEngine Context
    ///
    Scene(RenderEngine *engine);

    ///
    /// \brief Draw the Scene
    ///
    void Draw();

    void SetLightSourceMatrix(QMatrix4x4 lightMatrix);
    Drawable* GetLightSource();

    void CreateBlock();

    void AddBlock(QVector3D size, QVector3D transform, QVector4D color, Drawable *parent);
    void AddSphere(QVector3D size, QVector3D transform, QVector4D color, Drawable *parent);
    void AddDrawable(Drawable *drawable, QVector3D color, Drawable *parent);

    virtual void Update() = 0;
    virtual void Create() = 0;


protected:
    Drawable* m_lightSource;                    ///< lightsource of this scene
    std::vector<Drawable*> m_objects;           ///< Container for all Objects
    RenderEngine *m_engine;                     ///< RenderEngine Context
    Factory *m_factory;                         ///< Factory to Generate Drawables
};

#endif // SCENE_H
