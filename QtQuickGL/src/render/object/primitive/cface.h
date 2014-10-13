#ifndef CFACE_H
#define CFACE_H

class CFace
{
public:
    CFace();
private:
    int objID;
    int colorID;
    int edgeCount;
    int edges[4];
};

#endif // CFACE_H
