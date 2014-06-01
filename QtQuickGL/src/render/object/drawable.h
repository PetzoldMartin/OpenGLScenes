#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>       // for container drawable
#include <QVector4D>    // for color

// Forward Declaration
class QOpenGLShaderProgram;
class QMatrix4x4;
class QVector4D;
class QObject;
class RenderEngine;
class Mesh;

///
/// \brief The Drawable class
/// \author Andre Furchner
///
class Drawable
{
public:

    ///
    /// \brief Create a new Drawable
    /// \param engine RenderEngine Enviroment
    /// \param transform Transformation to parent
    ///
    Drawable(RenderEngine *engine, QMatrix4x4 *transform);

    ///
    /// \brief Draw the Drawable
    /// \param transform The SceneGraph transformation
    ///
    void Draw(QMatrix4x4* transform);

    ///
    /// \brief Complete the Model
    ///
    void Build();

    ///
    /// \brief Set the Mesh that is used to draw the Drawable
    /// \param mesh The Mesh
    ///
    void SetMesh(Mesh *mesh);

    ///
    /// \brief Set the Shader that is used to draw
    /// \param shader The Shader
    ///
    void SetShader(QOpenGLShaderProgram *shader);

    ///
    /// \brief Set the Model Matrix
    /// \param matrix The Model Matrix
    ///
    void SetModelMatrix(QMatrix4x4 *matrix);

    ///
    /// \brief Set the TransformMatrix to his parent
    /// \param matrix The transform from parant to this Drawable
    ///
    void SetTransformMatrix(QMatrix4x4 *matrix);

    ///
    /// \brief Add a Child to this Drawable with an transform offset
    /// \param child The Child
    /// \param transform The transform matrix to this Drawable
    ///
    void AddChild(Drawable *child, QMatrix4x4 *transform);

    ///
    /// \brief Set the Color
    /// \param color The Color
    ///
    void SetColor(QVector4D color);

    ///
    /// \brief Get the Child that is on the specific index
    /// \param index Child Index
    /// \return
    ///
    Drawable *GetChild(int index);

    ///
    /// \brief Get the Number of Child that ne Drawable has
    /// \return Number of Childs
    ///
    int GetChildCount();

    ///
    /// \brief Get the TransformMatrix to his parent
    /// \return The Transform Matrix
    ///
    QMatrix4x4 *GetTransformMatrix();

    ///
    /// \brief GetID returns the unique id
    /// \return the id
    ///
    QVector4D GetID();
    ///
    /// \brief GetID returns the unique id
    /// \return the id
    ///
    QVector4D makeNewID();
private:
    Mesh *m_mesh;                               ///< Geometry Mesh
    QVector4D m_color;                          ///< Color for Shader

    QOpenGLShaderProgram *m_shader;             ///< Used Shader to Draw
    RenderEngine *m_engine;                     ///< The RenderEngine Context

    QMatrix4x4 *m_modelMatrix;                  ///< Self Matrix
    QMatrix4x4 *m_transMatrix;                  ///< Transformation to his parent

    std::vector<Drawable*> m_childList;         ///< List of Childs

    QVector4D m_id;                             ///< unique id
    static QVector4D s_idCount;                 ///< gloabal count of all Drawables
};

#endif // DRAWABLE_H
