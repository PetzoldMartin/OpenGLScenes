#ifndef SCENE_H
#define SCENE_H

#include <vector>

class Drawable;
class RenderEngine;
class Factory;

#include <QQuickItem>

class Scene : public QQuickItem
{
    //Q_OBJECT
    //Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)
public:
    Scene(RenderEngine *engine);

    //qreal t() const { return m_t; }
    //void setT(qreal t);

    virtual void Draw();
    virtual void Update() = 0;
    virtual void Create() = 0;

signals:
    void tChanged();

public slots:
    int CreateDrawable(int type, QVector2D position);
    int GetID(QVector2D position);
    void Change(int id, int operation, QVector4D value);

protected:
    std::vector<Drawable*> m_objects;
    RenderEngine *m_engine;
    Factory *m_factory;

};

#endif // SCENE_H
