#include "cface.h"

CFace::CFace()
{
}
void CFace::addEdge(const CEdge &edge) {
    mEdges.push_back(edge);
}
