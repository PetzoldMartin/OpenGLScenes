#ifndef CFACE_H
#define CFACE_H

#include <qvector.h>

#include "cedge.h"

class CFace
{
public:
    CFace();
    void addEdge(const CEdge &edge) {this->mEdges.push_back(edge); };
    void setColor(const Qt::GlobalColor color) { this->color=color; };
private:
    QVector<CEdge> mEdges;
    Qt::GlobalColor color;
};

#endif // CFACE_H
