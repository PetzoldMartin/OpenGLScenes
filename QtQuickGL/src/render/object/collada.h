#ifndef COLLADA_H
#define COLLADA_H

#include <QString>
#include <QFile>

class Collada
{
public:
    Collada(const QString fileName);
private:
    void parse(QFile &xml);
    void readFloatArray();
    void readIndexArray();
    void readStride();
};

#endif // COLLADA_H
