#ifndef CFACE_H
#define CFACE_H

#include <qvector.h>

#include "cedge.h"

class CFace
{
public:
    CFace();
    void addEdge(const CEdge &edge);
private:
    QVector<CEdge> mEdges;
};

#endif // CFACE_H
