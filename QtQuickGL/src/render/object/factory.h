#ifndef FACTORY_H
#define FACTORY_H

class Drawable;
class QOpenGLShaderProgram;
class QVector4D;
class RenderEngine;

class Factory
{
public:
    Factory(RenderEngine *engine);

    Drawable *GenRectangle(float width, float height, QVector4D color, QOpenGLShaderProgram *shader);
private:
    RenderEngine *m_engine;
};

#endif // FACTORY_H
