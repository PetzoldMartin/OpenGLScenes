#include "collada.h"

#include <iostream>
#include <QTextStream>

using namespace std;

Collada::Collada(const QString fileName)
{

    // Try open file
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        parse(file);
        convert();
    } else {
        cerr << "Cant open File: " << fileName.toStdString() << endl;
    }

}
float *Collada::getPositions() const
{
    return iPositionBuffer;
}

float *Collada::getNormals() const
{
    return iNormalBuffer;
}

float *Collada::getTexCoords() const
{
    return iTexCoordBuffer;
}

int Collada::getIndexCount() const
{
    return indexCount;
}

void Collada:: parse(QFile& file) {

    QXmlStreamReader xml(&file);

    while (!xml.atEnd()) {
        if (xml.readNextStartElement()) {

            if (xml.name() == "float_array") {
                readFloatArray(xml);
            } else if (xml.name() == "polylist") {
                readIndexArray(xml);
            }
        }
    }
}

void Collada::readFloatArray(QXmlStreamReader& xml) {

    // read the array size and allocate mem
    int count = xml.attributes().value("count").toInt();
    float* buf = new float[count];

    // get the big float string from xml
    QString str_array = xml.readElementText();

    // convert string to float array
    int i = -1;
    QTextStream ts(&str_array);
    while(!ts.atEnd()) {
        ts >> buf[++i];
    }

    buffer.append(buf);
}

void Collada::readIndexArray(QXmlStreamReader& xml) {

    // read the array size and allocate mem
    int count = xml.attributes().value("count").toInt();
    indices = new int[count];

    // skip to indices
    while(!xml.atEnd()) {
        if (xml.readNextStartElement()) {
            if(xml.name() == "p") {
                break;
            }
        }
    }

    // get the big float string from xml
    QString str_array = xml.readElementText();

    // convert string to float array
    int i = -1;
    QTextStream ts(&str_array);
    while(!ts.atEnd()) {
        ts >> indices[++i];
    }

    // calculate index count per vertex
    //                    p   n   t
    indexCount = count / 8;
}

void Collada::convert() {

    // alloc mem
    iPositionBuffer = new float[indexCount * 3];
    iNormalBuffer = new float[indexCount * 3];
    iTexCoordBuffer = new float[indexCount * 2];

    // init convert pointer
    float* pPosI = iPositionBuffer -1;
    float* pNorI = iNormalBuffer -1;
    float* pTexI = iTexCoordBuffer -1;

    float* pPosB = buffer.at(0) -1;
    float* pNorB = buffer.at(1) -1;
    float* pTexB = buffer.at(2) -1;

    // convert to indexed order
    for(int i = 0; i < indexCount; ++i) {

        // Positions
        *(++pPosI) = *(++pPosB); // X
        *(++pPosI) = *(++pPosB); // Y
        *(++pPosI) = *(++pPosB); // Z

        // Normals
        *(++pNorI) = *(++pNorB); // X
        *(++pNorI) = *(++pNorB); // Y
        *(++pNorI) = *(++pNorB); // Z

        // TexCoords
        *(++pTexI) = *(++pTexB); // U
        *(++pTexI) = *(++pTexB); // V

    }
}


