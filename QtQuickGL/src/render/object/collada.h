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
    QString getDefuseTextureName() const;
    int getIndexCount() const;

private:
    QVector<float*> buffer;

    int* indices;
    int indexCount;

    // Converted Buffers
    float* iPositionBuffer;
    float* iNormalBuffer;
    float* iTexCoordBuffer;

    QString defuseTextureName;

    void parse(QFile &xml);
    void readFloatArray(QXmlStreamReader& xml);
    void readIndexArray(QXmlStreamReader& xml);
    void readImage(QXmlStreamReader& xml);

    void convert();
    void goTo(QXmlStreamReader& xml, QString name);
};

#endif // COLLADA_H
