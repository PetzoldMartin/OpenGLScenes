#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>       // container drawable
#include <QVector4D>    // color
#include <QMatrix4x4>   // model and transform Matrix
#include <QOpenGLTexture>

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
    void TranslateSelectedRelative(QVector3D transform);
    ///
    /// \brief Rotate the Drawable itself
    /// \param angle rotation angle (deg)
    /// \param axis rotation axis
    ///
    void RotateDirect(int deltax, int deltay,int deltaz);

    ///
    /// \brief Rotate the Drawable relative to his parent
    /// \param angle rotation angle (deg)
    /// \param axis rotation axis
    ///
    void RotateRelative(float angle, QVector3D axis);
    void RotateSelectedRelative(int deltax, int deltay, int deltaz);
    ///
    /// \brief ManipulateSelected do the Manipulation of the selected item Temporarly until force is triggert
    ///
    void ManipulateSelected();
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
    /// \brief Set the Texture
    /// \param String Location of the texture in recourses
    ///
    void SetTexture(QOpenGLTexture *texture);

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

    ///
    /// \brief GetDrawableByID returns the drawable referenced to the ID
    /// \return the Drawable Pointer
    ///
    static Drawable* GetDrawableByID(QVector4D ID);

    QMatrix4x4 GetSceneMatrix();
    ///
    /// \brief scale the selected objekt
    /// \param factor scaling factor
    ///
    void scaleSelected(float factor);
    void forceModification();

    std::vector<Drawable*> m_childList;                                 ///< List of Childs


private:

    ///
    /// \brief Generates a new unique ID
    /// \return the unique id
    ///
    std::vector<unsigned char> makeNewID();


    Mesh *m_mesh;                                                       ///< Geometry Mesh
    QVector4D m_color;                                                  ///< Color for Shader

    QOpenGLShaderProgram *m_shader;                                     ///< Used Shader to Draw
    RenderEngine *m_engine;                                             ///< The RenderEngine Context

    QMatrix4x4 m_modelMatrix;                                           ///< Self Matrix
    QMatrix4x4 m_transMatrix;                                           ///< Transformation to his parent
    QMatrix4x4 m_manipulateMatrix;                                      ///< Temporary for Object direct manipulating
    QMatrix4x4 m_manipulateRMatrix;                                     ///< Temporary for Object relativ manipulating


    std::vector<unsigned char> m_id;                                    ///< unique id
    static std::vector<unsigned char> s_idCount;                        ///< gloabal count of all Drawables
    static QMap<std::vector<unsigned char>,Drawable*> s_drawableMap;
    bool m_isSelected;                                                  ///< Flag for an Selected Drawable
    QMatrix4x4 m_SceneMatrix;
    int xr,yr,zr;
    float scale_value;                                                       ///< Buffer for rotation angles as float
    QVector3D m_transform;
    QOpenGLTexture *m_texture;                                          ///< QT OpenGL Texture of the Drawable
};

#endif // DRAWABLE_H
