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
    } else {
        cerr << "Cant open File: " << fileName.toStdString() << endl;
    }

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
        if (xml.readNextStartElement() && xml.name() == "p") {
            break;
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
}

void Collada::readStride(QXmlStreamReader& xml) {

}


