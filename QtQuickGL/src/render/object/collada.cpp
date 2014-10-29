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

QString Collada::getDefuseTextureName() const
{
    return defuseTextureName;
}

int Collada::getIndexCount() const
{
    return indexCount;
}

void Collada:: parse(QFile& file) {

    QXmlStreamReader xml(&file);

    while (!xml.atEnd()) {
        if (xml.readNextStartElement()) {
            // seach for needed informations
            if (xml.name() == "image") {
                readImage(xml);
            } else if (xml.name() == "float_array") {
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
    goTo(xml, "p");

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

void Collada::readImage(QXmlStreamReader &xml)
{
    QString id = xml.attributes().value("id").toString();
    goTo(xml,"init_from");
    QString textureName = xml.readElementText();

    //if(id == "defuse")
        defuseTextureName = textureName;
    // to be continued for more textures...
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

    // start converting
    for(int i = 0; i < indexCount*3; i += 3) {
        *(++pPosI) = pPosB[indices[i] * 3 + 0];
        *(++pPosI) = pPosB[indices[i] * 3 + 1];
        *(++pPosI) = pPosB[indices[i] * 3 + 2];

        *(++pNorI) = pNorB[indices[i+1] * 3 + 0];
        *(++pNorI) = pNorB[indices[i+1] * 3 + 1];
        *(++pNorI) = pNorB[indices[i+1] * 3 + 2];

        *(++pTexI) = pTexB[indices[i+2] * 2 + 0];
        *(++pTexI) = 1.0f - pTexB[indices[i+2] * 2 + 1];
    }
}

void Collada::goTo(QXmlStreamReader &xml, QString name)
{
    // skip to name
    bool finish = false;
    while(!xml.atEnd() && !finish) {
        if (xml.readNextStartElement()) {
            if(xml.name() == name) {
                finish = true;
            }
        }
    }
}


