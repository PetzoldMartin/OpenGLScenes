#ifndef CVERTEX_H
#define CVERTEX_H

#include <QVector3D>

class CVertex
{
public:
    CVertex();
    QVector3D position() const;
    void setPosition(const QVector3D &position);

private:
    QVector3D mPosition;
};

#endif // CVERTEX_H
