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

    float *getPositions() const;
    float *getNormals() const;
    float *getTexCoords() const;
    int getIndexCount() const;

private:
    QVector<float*> buffer;

    int* indices;
    int indexCount;

    float* iPositionBuffer;
    float* iNormalBuffer;
    float* iTexCoordBuffer;

    void parse(QFile &xml);
    void readFloatArray(QXmlStreamReader& xml);
    void readIndexArray(QXmlStreamReader& xml);
    void convert();
};

#endif // COLLADA_H
