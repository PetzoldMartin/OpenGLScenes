#include "cedge.h"

CEdge::CEdge()
{
}

void CEdge::addVertex(const CVertex &vertex) {
    mVertecies.push_back(vertex);
}
