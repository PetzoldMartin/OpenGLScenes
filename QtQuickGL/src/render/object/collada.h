#ifndef COLLADA_H
#define COLLADA_H

#include <QXmlStreamReader>
#include <QVector>
#include <QString>
#include <QFile>

class Collada
{
public:
    Collada(const QString fileName);
private:
    QVector<float*> buffer;
    int* indices;

    void parse(QFile &xml);
    void readFloatArray(QXmlStreamReader& xml);
    void readIndexArray(QXmlStreamReader& xml);
    void readStride(QXmlStreamReader& xml);
};

#endif // COLLADA_H
