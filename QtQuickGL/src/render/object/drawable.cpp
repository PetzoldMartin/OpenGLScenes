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

vector<unsigned char> Drawable::s_idCount(4,0);

Drawable::Drawable(RenderEngine *engine, QMatrix4x4 transform)
{
    m_shader = NULL;
    m_mesh = NULL;
    m_modelMatrix.setToIdentity();
    m_engine = engine;
    m_transMatrix = transform;
    m_isSelected = false;

    // create new id
    // TODO: make this better



    m_id=makeNewID();
    //SetColor(m_id);



}

vector<unsigned char> Drawable::makeNewID(){
    vector<unsigned char>v(4,255);
    s_idCount[0]+=32;
    ++v[0]=s_idCount[0];
    ++v[1]=200;
    ++v[2]=200;
    ++v[3]=255;
    cout<<(float)v[0]/255<<"x "<<(float)v[1]/255<<"y "<<(float)v[2]/255<<"z "<<(float)v[3]/255<<endl;

    return v;
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
<<<<<<< local
    m_shader->setUniformValue("id",QVector4D((float)m_id[0]/255,(float)m_id[1]/255,(float)m_id[2]/255,(float)m_id[3]/255));
=======
    m_shader->setUniformValue("id", m_id);
    if(m_isSelected) m_shader->setUniformValue("isSelected", 1.0f);
    else m_shader->setUniformValue("isSelected", 0.0f);

>>>>>>> other

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

void Drawable::SetSelected(bool value)
{
    m_isSelected = value;
}

Drawable *Drawable::GetChild(int index)
{
    return m_childList[index];
}

int Drawable::GetChildCount()
{
    return m_childList.size();
}


vector<unsigned char> Drawable::GetID()
{
    return m_id;
}
