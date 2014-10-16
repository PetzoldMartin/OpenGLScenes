#ifndef CEDGE_H
#define CEDGE_H

#include <QVector>

#include "cvertex.h"

class CEdge
{
public:
    CEdge();
    void addVertex(const CVertex &vertex);
private:
    QVector<CVertex> mVertecies;
};

#endif // CEDGE_H
