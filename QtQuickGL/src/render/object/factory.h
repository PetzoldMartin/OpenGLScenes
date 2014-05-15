#ifndef FACTORY_H
#define FACTORY_H

class Drawable;
class QOpenGLShaderProgram;
class QVector4D;
class QVector3D;
class RenderEngine;

class Factory
{
public:
    Factory(RenderEngine *engine);

    Drawable *GenRectangle(QVector3D size, QVector4D color, QOpenGLShaderProgram *shader);
private:
    RenderEngine *m_engine;
};

#endif // FACTORY_H
