#include "collada.h"

#include <QXmlStreamReader>
#include <iostream>

using namespace std;

Collada::Collada(const QString fileName)
{

    // Try open file
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        parse(file);
    } else {
        cerr << "Cant open File: " << fileName.toStdString() << endl;
    }

}

void Collada:: parse(QFile& file) {

    QXmlStreamReader xml(&file);

    while (!xml.atEnd()) {
        if (xml.readNextStartElement()) {
            if (xml.name() == "float_array") {
                readFloatArray();
            } else if (xml.name() == "accessor") {
                readStride();
            } else if (xml.name() == "polylist") {
                readIndexArray();
            }
        }
    }

}

void Collada::readFloatArray() {

}

void Collada::readStride() {

}

void Collada::readIndexArray() {

}
