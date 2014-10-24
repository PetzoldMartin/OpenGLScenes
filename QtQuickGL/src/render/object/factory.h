#ifndef FACTORY_H
#define FACTORY_H

class Drawable;
class QOpenGLShaderProgram;
class QVector4D;
class QVector3D;
class RenderEngine;
class Mesh;
class QFile;
class QString;

///
/// \brief The Factory class Produces Drawables
/// \author André Furchner
///
class Factory
{
public:

    ///
    /// \brief Create a new Factory
    /// \param engine The RenderEngine Context
    ///
    Factory(RenderEngine *engine);

    ///
    /// \brief Generate a new Rectangle
    /// \param size Size of the Rectangle
    /// \param color Color for the Rectangle
    /// \param shader Shader to be used when Draw
    /// \return A new Drawable that is a Rectangle
    ///
    Drawable *GenRectangle(QVector3D size, QVector4D color);

    ///
    /// \brief Generate a new Block
    /// \param size Size of the Block
    /// \param color Color for the Block
    /// \param shader Shader to be used when Draw
    /// \return A new Drawable that is a Block
    ///
    Drawable *GenBlock(QVector3D size, QVector4D color);

    ///
    /// \brief Generate a new Sphere
    /// \param size Size for the Sphere
    /// \param color Color
    /// \return
    ///
    Drawable *GenSphere(QVector3D size, QVector4D color);

    ///
    /// \brief Generate a new Model from a file
    /// \param file file to read from
    /// \param size scale factor of the model
    /// \param color Color
    /// \return
    ///
    Drawable *GenFromFile(QFile* file, QVector4D color, QVector3D size);

    ///
    /// \brief Generate a new Model an collada file
    /// \param name Folder name
    /// \param size scale factor of the model
    /// \param color Color
    /// \return
    ///
    Drawable *GenCollada(const QString name, QVector3D size, QVector4D color);
private:

    RenderEngine *m_engine;         ///< The RenderEngine Context
    Mesh *m_rectangle;              ///< The Default Rectangle Mesh
    Mesh *m_block;                  ///< The Default Block Mesh
    Mesh *m_sphere;
    Mesh *generateMeshFromFile(QFile *file);
    void createMeshRectangle();
    void createMeshBlock();
    void createMeshSphere();
};

#endif // FACTORY_H
