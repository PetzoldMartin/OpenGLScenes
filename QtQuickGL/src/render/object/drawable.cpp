#include "drawable.h"
#include "src/io/console.h"
#include "src/render/render_engine.h"
#include "src/render/object/mesh.h"
#include <iostream>
#include <cmath>

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
using namespace std;

QVector4D Drawable::s_idCount = QVector4D(0.0f,0.0f,0.0f,1.0f);

Drawable::Drawable(RenderEngine *engine, QMatrix4x4 transform)
{
    m_shader = NULL;
    m_mesh = NULL;
    m_modelMatrix.setToIdentity();
    m_engine = engine;
    m_transMatrix = transform;

    // create new id
    // TODO: make this better



    m_id=makeNewID();
    //SetColor(m_id);

    cout<<m_id.x()<<"x "<<m_id.y()<<"y "<<m_id.z()<<"z "<<endl;

}

QVector4D Drawable::makeNewID(){
    unsigned long i=(unsigned long) this;
    unsigned long t=1000;
    float b[3];
    if(s_idCount.x()<=0.9f)
    s_idCount.setX((s_idCount.x()+0.3f));
    else
    s_idCount.setX(0.0f);
    b[0] = ((float)(((i/1000000)%t)%100))/t;
    b[1] = ((float)((i/1000)%t))/t;
    b[2] = ((float)((i)%t))/t;
    return QVector4D(b[0],b[1],b[2],1.0f)+s_idCount;
}

void Drawable::Draw(QMatrix4x4 *transform)
{
    // bind my shader to be used
    m_shader->bind();

    // set my uniform color
    m_shader->setUniformValue("color", m_color);

    // calculate and set uniform variable modelMatrix
    QMatrix4x4 sceneMatrix = *transform * m_transMatrix;
    m_shader->setUniformValue("modelMatrix", sceneMatrix * m_modelMatrix);
    m_shader->setUniformValue("sceneMatrix",sceneMatrix);
    m_shader->setUniformValue("id", m_id);

    // draw myself
    m_mesh->Draw();
    m_shader->release();

    // draw my childs
    for(unsigned int i = 0; i < m_childList.size(); ++i) {
        m_childList[i]->Draw(&sceneMatrix);
    }
}

void Drawable::Build()
{
    // first check for wrong usage
    if(m_shader == NULL) {
        Console::WriteError("No Shader assigned for this Drawable!");
        return;
    }

    if(m_mesh == NULL) {
        Console::WriteError("No Mesh is assigned to this Drawable!");
        return;
    }

    // set uniform variable
    m_shader->setUniformValue("modelMatrix", m_modelMatrix);
    m_mesh->BuildVAO(m_engine->GetContext(), m_shader);

}

void Drawable::TranslateDirect(QVector3D transform)
{
    m_modelMatrix.translate(transform);
}

void Drawable::TranslateRelative(QVector3D transform)
{
    m_transMatrix.translate(transform);
}

void Drawable::RotateDirect(float angle, QVector3D axis)
{
    m_modelMatrix.rotate(angle, axis);
}

void Drawable::RotateRelative(float angle, QVector3D axis)
{
    m_transMatrix.rotate(angle, axis);
}

void Drawable::SetMesh(Mesh *mesh)
{
    m_mesh = mesh;
}

void Drawable::SetShader(QOpenGLShaderProgram *shader)
{
    m_shader = shader;
}

void Drawable::SetModelMatrix(QMatrix4x4 matrix)
{
    m_modelMatrix = matrix;
}

QMatrix4x4 Drawable::GetModelMatrix()
{
    return m_modelMatrix;
}

void Drawable::SetTransformMatrix(QMatrix4x4 matrix)
{
    m_transMatrix = matrix;
}

QMatrix4x4 Drawable::GetTransformMatrix()
{
    return m_transMatrix;
}

void Drawable::AddChild(Drawable *child, QMatrix4x4 transform)
{
    child->m_transMatrix = transform;
    m_childList.push_back(child);
}

void Drawable::SetColor(QVector4D color)
{
    m_color = color;
}

Drawable *Drawable::GetChild(int index)
{
    return m_childList[index];
}

int Drawable::GetChildCount()
{
    return m_childList.size();
}


QVector4D Drawable::GetID()
{
    return m_id;
}
