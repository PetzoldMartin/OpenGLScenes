#include "cvertex.h"

CVertex::CVertex()
{
    mPosition.setX(0);
    mPosition.setY(0);
    mPosition.setZ(0);
}
QVector3D CVertex::position() const
{
    return mPosition;
}

void CVertex::setPosition(const QVector3D &position)
{
    mPosition = position;
}

