#ifndef FACTORY_H
#define FACTORY_H

class QObject;
class Drawable;
class QOpenGLShaderProgram;

class Factory
{
public:
    Factory(QObject *parent);

    Drawable *GenRectangle(float width, float height, QOpenGLShaderProgram *shader);
private:
    QObject *m_parent;

    void createBasicRectange();
};

#endif // FACTORY_H
