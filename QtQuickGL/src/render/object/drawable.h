#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>       // container drawable
#include <QVector4D>    // color
#include <QMatrix4x4>   // model and transform Matrix

// Forward Declaration
class QOpenGLShaderProgram;
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
    Drawable(RenderEngine *engine, QMatrix4x4 transform);

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
    /// \brief Translate the Modle itself
    /// \param transform Transformation value
    ///
    void TranslateDirect(QVector3D transform);

    ///
    /// \brief Translate the Drawable relative to his parent
    /// \param transform Tranformation value
    ///
    void TranslateRelative(QVector3D transform);

    ///
    /// \brief Rotate the Drawable itself
    /// \param angle rotation angle (deg)
    /// \param axis rotation axis
    ///
    void RotateDirect(float angle, QVector3D axis);

    ///
    /// \brief Rotate the Drawable relative to his parent
    /// \param angle rotation angle (deg)
    /// \param axis rotation axis
    ///
    void RotateRelative(float angle, QVector3D axis);

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
    void SetModelMatrix(QMatrix4x4 matrix);

    ///
    /// \brief Returns the ModelMatrix
    /// \return ModelMatrix
    ///
    QMatrix4x4 GetModelMatrix();

    ///
    /// \brief Set the TransformMatrix to his parent
    /// \param matrix The transform from parant to this Drawable
    ///
    void SetTransformMatrix(QMatrix4x4 matrix);

    ///
    /// \brief Get the TransformMatrix to his parent
    /// \return The Transform Matrix
    ///
    QMatrix4x4 GetTransformMatrix();

    ///
    /// \brief Add a Child to this Drawable with an transform offset
    /// \param child The Child
    /// \param transform The transform matrix to this Drawable
    ///
    void AddChild(Drawable *child, QMatrix4x4 transform);

    ///
    /// \brief Set the Color
    /// \param color The Color
    ///
    void SetColor(QVector4D color);

    ///
    /// \brief Set the isSelected Flag
    /// \param value the Flag
    ///
    void SetSelected(bool value);

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
    /// \brief GetID returns the unique id
    /// \return the id
    ///
    std::vector<unsigned char> GetID();

private:

    ///
    /// \brief Generates a new unique ID
    /// \return the unique id
    ///
    std::vector<unsigned char> makeNewID();


    Mesh *m_mesh;                               ///< Geometry Mesh
    QVector4D m_color;                          ///< Color for Shader

    QOpenGLShaderProgram *m_shader;             ///< Used Shader to Draw
    RenderEngine *m_engine;                     ///< The RenderEngine Context

    QMatrix4x4 m_modelMatrix;                   ///< Self Matrix
    QMatrix4x4 m_transMatrix;                   ///< Transformation to his parent

    std::vector<Drawable*> m_childList;         ///< List of Childs

    std::vector<unsigned char> m_id;                             ///< unique id
    static std::vector<unsigned char> s_idCount;                 ///< gloabal count of all Drawables
    //static QMap<Drawable,std::vector drawable_map
    bool m_isSelected;                            ///< Flag for an Selected Drawable

};

#endif // DRAWABLE_H
