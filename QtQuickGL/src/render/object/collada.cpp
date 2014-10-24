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
    int count = xml.attributes().value("count").toInt() *8 * 3;
    indices = new int[count];

    // skip to indices
    bool finish = false;
    while(!xml.atEnd() && !finish) {
        if (xml.readNextStartElement()) {
            if(xml.name() == "p") {
                finish = true;
            }
        }
    }

    // get the big float string from xml
    QString str_array = xml.readElementText();

    // convert string to float array
    int i = -1;
    QTextStream ts(&str_array);
    cout << "blub";
    while(!ts.atEnd()) {
        ts >> indices[++i];
    }

    // calculate index count per vertex
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

    float* pPosB = buffer[0];
    float* pNorB = buffer[1];
    float* pTexB = buffer[2];

    int* pIndB = indices -1;

    // convert to indexed order
    /*
    for(int i = 0; i < indexCount; i += 3) {

        // Positions
        ++pIndB;
        *(++pPosI) = pPosB[*pIndB * 3]; // X
        *(++pPosI) = pPosB[*pIndB * 3 + 1]; // Y
        *(++pPosI) = pPosB[*pIndB * 3 + 2]; // Z

        // Normals
        ++pIndB;
        *(++pNorI) = pNorB[*pIndB * 3]; // X
        *(++pNorI) = pNorB[*pIndB * 3 + 1]; // Y
        *(++pNorI) = pNorB[*pIndB * 3 + 2]; // Z

        // TexCoords
        ++pIndB;
        *(++pTexI) = pTexB[*(++pIndB)]; // U
        *(++pTexI) = pTexB[*(++pIndB)]; // V
    }
    */



    int p = -1;
    int n = -1;
    int t = -1;
    for(int i = 0; i < indexCount*3; i += 3) {
        iPositionBuffer[++p] = pPosB[indices[i] * 3 + 0];
        iPositionBuffer[++p] = pPosB[indices[i] * 3 + 1];
        iPositionBuffer[++p] = pPosB[indices[i] * 3 + 2];

        iNormalBuffer[++n] = pNorB[indices[i+1] * 3 + 0];
        iNormalBuffer[++n] = pNorB[indices[i+1] * 3 + 1];
        iNormalBuffer[++n] = pNorB[indices[i+1] * 3 + 2];

        iTexCoordBuffer[++t] = pTexB[indices[i+2] * 2 + 0];
        iTexCoordBuffer[++t] = pTexB[indices[i+2] * 2 + 1];
    }
}


