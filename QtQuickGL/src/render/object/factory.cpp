#include "factory.h"

#include "src/render/object/drawable.h"
#include "src/render/render_engine.h"
#include "src/render/object/mesh.h"
#include "src/io/console.h"

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QVector4D>
#include <QDataStream>
#include <glm/glm.hpp>
#include <iostream>
#include <QFile>


Factory::Factory(RenderEngine *engine)
{
    m_engine = engine;
    m_rectangle = NULL;
    m_block = NULL;
    m_sphere = NULL;

    createMeshRectangle();
    createMeshBlock();
    createMeshSphere();
}

Mesh *Factory::generateMeshFromFile(QFile* file){

    file->open(QIODevice::ReadOnly);
    //QMap<QString, QVector < QVector <int> > > data;
    QVector<QPair<QPair<QString,int>, QVector<int> > > data;
    while (!file->atEnd()) {
        QTextStream stream(file->readLine());

        QString sType; // element type
        stream >> sType;

        int id; // element id
        stream >> id;


        //qDebug() << sType << "\t" << id;

        QVector<int> line;

        // face color
        if (!sType.compare("F",Qt::CaseInsensitive)) {
            int color;
            stream >> color;
            line.push_back(color);
           // qDebug() << color << "\t" << sType;
        }

        while (true) {

            int var;
            stream >> var;

            if (stream.atEnd()) {
                break;
            }

            line.push_back(var);
        }
        //qDebug() << line;
        data.push_back(QPair<QPair<QString,int>, QVector<int> >(QPair<QString,int>(sType,id),line));
    }
    qDebug() << data;
    return NULL;
}


Drawable *Factory::GenFromFile(QFile* file, QVector4D color, QVector3D size) {
    // create internal model matrix that create the size
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.scale(size);

    // create a new Drawable from file
    Drawable *model = new Drawable(m_engine, QMatrix4x4());
    Mesh *modelMesh = generateMeshFromFile(file);

    model->SetMesh(modelMesh);
    model->SetModelMatrix(modelMatrix);
    model->SetShader(m_engine->GetShader("basic")); //TODO new Shader
    model->SetColor(color);

    return model;
}

Drawable* Factory::GenRectangle(QVector3D size,  QVector4D color) {

    // create internal model matrix that create the size
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.scale(size);

    // create a new Drawable to be a Rectangle
    Drawable *rect = new Drawable(m_engine, QMatrix4x4());
    rect->SetMesh(m_rectangle);
    rect->SetModelMatrix(modelMatrix);
    rect->SetShader(m_engine->GetShader("basic"));
    rect->SetColor(color);

    return rect;
}

Drawable *Factory::GenBlock(QVector3D size, QVector4D color)
{
    // create internal model matrix that create the size
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.scale(size);

    // create a new Drawable to be a Block
    Drawable *block = new Drawable(m_engine, QMatrix4x4());
    block->SetMesh(m_block);
    block->SetModelMatrix(modelMatrix);
    block->SetShader(m_engine->GetShader("basic"));
    block->SetColor(color);

    return block;
}

Drawable *Factory::GenSphere(QVector3D size, QVector4D color)
{
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.scale(size);
    Drawable *sphere = new Drawable(m_engine, QMatrix4x4());
    sphere->SetMesh(m_sphere);
    sphere->SetModelMatrix(modelMatrix);
    sphere->SetShader(m_engine->GetShader("basic"));
    sphere->SetColor(color);

    return sphere;
}

void Factory::createMeshRectangle()
{
    QVector3D normal[] = {
        QVector3D(+0.0, -1.0, +0.0),
        QVector3D(+0.0, -1.0, +0.0),
        QVector3D(+0.0, -1.0, +0.0),

        QVector3D(+0.0, -1.0, +0.0),
        QVector3D(+0.0, -1.0, +0.0),
        QVector3D(+0.0, -1.0, +0.0),
    };

    QVector3D vert[] = {
        QVector3D(+0.5, +0.0, +0.5),
        QVector3D(-0.5, -0.0, -0.5),
        QVector3D(-0.5, +0.0, +0.5),

        QVector3D(+0.5, +0.0, +0.5),
        QVector3D(+0.5, -0.0, -0.5),
        QVector3D(-0.5, -0.0, -0.5),
    };

    m_rectangle = new Mesh();
    m_rectangle->SetVertices(vert,6);
    m_rectangle->SetNormals(normal,6);
}

void Factory::createMeshBlock()
{
    QVector3D normal[] = {

        // TOP
        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),

        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),
        QVector3D(+0.0, +0.0, +1.0),


        // BOTOM
        QVector3D(+0.0, +0.0, -1.0),
        QVector3D(+0.0, +0.0, -1.0),
        QVector3D(+0.0, +0.0, -1.0),

        QVector3D(+0.0, +0.0, -1.0),
        QVector3D(+0.0, +0.0, -1.0),
        QVector3D(+0.0, +0.0, -1.0),


        // Left
        QVector3D(-1.0, +0.0, +0.0),
        QVector3D(-1.0, +0.0, +0.0),
        QVector3D(-1.0, +0.0, +0.0),

        QVector3D(-1.0, +0.0, +0.0),
        QVector3D(-1.0, +0.0, +0.0),
        QVector3D(-1.0, +0.0, +0.0),


        // Right
        QVector3D(+1.0, +0.0, +0.0),
        QVector3D(+1.0, +0.0, +0.0),
        QVector3D(+1.0, +0.0, +0.0),

        QVector3D(+1.0, +0.0, +0.0),
        QVector3D(+1.0, +0.0, +0.0),
        QVector3D(+1.0, +0.0, +0.0),


        // Back
        QVector3D(0.0, 1.0, +0.0),
        QVector3D(0.0, 1.0, +0.0),
        QVector3D(0.0, 1.0, +0.0),

        QVector3D(0.0, 1.0, +0.0),
        QVector3D(0.0, 1.0, +0.0),
        QVector3D(0.0, 1.0, +0.0),


        // Front
        QVector3D(0.0, -1.0, +0.0),
        QVector3D(0.0, -1.0, +0.0),
        QVector3D(0.0, -1.0, +0.0),

        QVector3D(0.0, -1.0, +0.0),
        QVector3D(0.0, -1.0, +0.0),
        QVector3D(0.0, -1.0, +0.0),
    };

    QVector3D vert[] = {

        // TOP
        QVector3D(+0.5, +0.5, +0.5),
        QVector3D(-0.5, +0.5, +0.5),
        QVector3D(-0.5, -0.5, +0.5),

        QVector3D(+0.5, +0.5, +0.5),
        QVector3D(-0.5, -0.5, +0.5),
        QVector3D(+0.5, -0.5, +0.5),


        // BOTOM
        QVector3D(-0.5, +0.5, -0.5),
        QVector3D(+0.5, +0.5, -0.5),
        QVector3D(-0.5, -0.5, -0.5),

        QVector3D(-0.5, -0.5, -0.5),
        QVector3D(+0.5, +0.5, -0.5),
        QVector3D(+0.5, -0.5, -0.5),


        // LEFT
        QVector3D( -0.5, -0.5, +0.5),
        QVector3D( -0.5, +0.5, +0.5),
        QVector3D( -0.5, -0.5, -0.5),

        QVector3D( -0.5, -0.5, -0.5),
        QVector3D( -0.5, +0.5, +0.5),
        QVector3D( -0.5, +0.5, -0.5),


        // RIGHT
        QVector3D( +0.5, +0.5, +0.5),
        QVector3D( +0.5, -0.5, +0.5),
        QVector3D( +0.5, -0.5, -0.5),

        QVector3D( +0.5, +0.5, +0.5),
        QVector3D( +0.5, -0.5, -0.5),
        QVector3D( +0.5, +0.5, -0.5),


        // BACK
        QVector3D( -0.5, +0.5, +0.5),
        QVector3D( +0.5, +0.5, +0.5),
        QVector3D( -0.5, +0.5, -0.5),

        QVector3D( -0.5, +0.5, -0.5),
        QVector3D( +0.5, +0.5, +0.5),
        QVector3D( +0.5, +0.5, -0.5),


        // FRONT
        QVector3D( +0.5, -0.5, +0.5),
        QVector3D( -0.5, -0.5, +0.5),
        QVector3D( -0.5, -0.5, -0.5),

        QVector3D( +0.5, -0.5, +0.5),
        QVector3D( -0.5, -0.5, -0.5),
        QVector3D( +0.5, -0.5, -0.5),

    };
    QVector2D tcoord[] = {
        // top
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+0.0),

        // bottom
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+0.0),

        // left
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+0.0),

        // right
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+0.0),

        // back
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+0.0),

        // front
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+1.0),
        QVector2D(+0.0,+0.0),
        QVector2D(+1.0,+0.0),
    };

    m_block = new Mesh();
    m_block->SetVertices(vert,36);
    m_block->SetNormals(normal,36);
    m_block->SetTextCoords(tcoord,36);
    m_block->BuildVAO(m_engine->GetContext(),m_engine->GetShader("basic"));

}

void Factory::createMeshSphere() {
    m_sphere=new Mesh();
    QVector<QVector3D> bodyVert;
    QVector<QVector3D> normals;
    QVector<QVector3D> vertecies;

    /** the infamous PI */
#ifndef PI
#define PI (3.1415926535897932384626433832795)
#endif

    /** 2.0 * PI */
#ifndef TWO_PI
#define TWO_PI (6.283185307179586476925286766559)
#endif

    float rad = 0.5;
    unsigned int segv = 8;
    unsigned int segu = 2*segv;


    for (unsigned int v = 1; v<segv; ++v)
    {
        // current vertex offset
        int rown = bodyVert.size();

        // body vertices
        for (unsigned int u = 0; u<segu; ++u)
        {
            float ut = (float)u / segu*TWO_PI;
            float vt= (float)v / segv*PI;

            glm::vec3 p = glm::vec3(
                        // rotate a point (0,1,0) around z
                        -sin(vt), std::cos(vt), 0 );
            // rotate this point around y
            p.z = -p.x * std::sin(ut);
            p.x =  p.x * std::cos(ut);
            bodyVert << QVector3D(p.x * rad, p.y * rad, p.z * rad);
        }

        // triangles on each 'row'
        for (unsigned int u = 0; u<segu; ++u)
        {
            // connect to top point
            if (v==1)
            {
                vertecies << (QVector3D(bodyVert.at(0)))
                          << (QVector3D(bodyVert.at(rown+u)))
                          << (QVector3D(bodyVert.at(rown+(u+1)%segu)));
                //  bodyVert->addTriangle(0, rown + u, rown + (u + 1) % segu);
            }
            else
            {
                vertecies << (QVector3D(bodyVert.at(rown - segu + u)))
                          << (QVector3D(bodyVert.at(rown + u)))
                          << (QVector3D(bodyVert.at(rown + (u + 1) % segu)));
                // connect
                //                m_sphere->addTriangle(
                //                            // previous row
                //                            rown - segu + u,
                //                            // with this row
                //                            rown + u, rown + (u + 1) % segu);
                vertecies << (QVector3D(bodyVert.at(rown - segu + (u + 1) % segu)))
                          << (QVector3D(bodyVert.at(rown - segu + u)))
                          << (QVector3D(bodyVert.at(rown + (u + 1) % segu)));
                //                // .. and the other triangle of the quad
                //                m_sphere->addTriangle(rown - segu + (u + 1) % segu,
                //                                      rown - segu + u,
                //                                      rown + (u + 1) % segu);
            }
        }
    }

    int rown = bodyVert.size() - segu - 1;

    // bottom point
    //m_sphere->addVertex(0, -rad, 0);
    vertecies << (QVector3D(bodyVert.at(0)))
              << (QVector3D(bodyVert.at(-rad)))
              << (QVector3D(bodyVert.at(0)));

    // connect to bottom point
    for (unsigned int u = 0; u<segu; ++u)
    {
        vertecies << (QVector3D(bodyVert.at(bodyVert.size()-1)))
                  << (QVector3D(bodyVert.at(rown + (u + 1) % segu)))
                  << (QVector3D(bodyVert.at(rown + u)));
        //        m_sphere->addTriangle(m->numVertices()-1,
        //                              rown + (u + 1) % segu, rown + u);
    }

    //    for (int i=0;i<vertecies.size();++i) {
    //        std::cout << vertecies.at(i).x() << "\t" << vertecies.at(i).y() << "\t" << vertecies.at(i).z() <<std::endl;
    //    }
    m_sphere->SetVertices(&(vertecies[0]),vertecies.size());

    // an array to memorize the number of
    // adjacent vertices for each vertex
    std::vector<size_t> nr_adds(vertecies.size());

    // for each triangle
    for (size_t i=0; i<vertecies.size()/3; ++i)
    {
        // vector of each triangle corner
        QVector3D p1 = vertecies.at(i*3),
                p2 = vertecies.at(i*3+1),
                p3 = vertecies.at(i*3+2);

        // calculate the normal of the triangle
        QVector3D n = QVector3D::crossProduct((p2-p1),(p3-p1));
        n.normalize();
        normals << QVector3D(n) << QVector3D(n) << QVector3D(n);
    }
    //m_sphere->SetNormals(&(vertecies[0]),vertecies.size());
    m_sphere->SetNormals(&(normals[0]),normals.size());
    m_sphere->BuildVAO(m_engine->GetContext(),m_engine->GetShader("basic"));
}


