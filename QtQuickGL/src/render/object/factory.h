#ifndef FACTORY_H
#define FACTORY_H

class QObject;
class Drawable;
class QOpenGLShaderProgram;
class QVector4D;

class Factory
{
public:
    Factory(QObject *parent);

    Drawable *GenRectangle(float width, float height, QVector4D color, QOpenGLShaderProgram *shader);
private:
    QObject *m_parent;

    void createBasicRectange();
};

#endif // FACTORY_H
