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
#include <qpixmap.h>
#include <QOpenGLTexture>
#include <qcolor.h>

using namespace std;

vector<unsigned char> Drawable::s_idCount(4,0);
QMap<vector<unsigned char>,Drawable*> Drawable::s_drawableMap;
Drawable::Drawable(RenderEngine *engine, QMatrix4x4 transform)
{
    m_shader = nullptr;
    m_mesh = nullptr;
    m_texture = nullptr;
    m_modelMatrix.setToIdentity();
    m_manipulateMatrix.setToIdentity();
    m_manipulateRMatrix.setToIdentity();
    m_engine = engine;
    m_transMatrix = transform;
    m_isSelected = false;
    yr=zr=xr=0;
    scale_value=1.0f;
    m_transform=QVector3D(0.0,0.0,0.0);
    // create new id
    // TODO: make this better


    m_id=makeNewID();
    s_drawableMap[m_id]=this;
    //SetColor(m_id);

}

vector<unsigned char> Drawable::makeNewID(){
    vector<unsigned char>v(4,255);
    s_idCount[0]+=3;
    s_idCount[1]-=7;
    s_idCount[2]+=23;
    ++v[0]=s_idCount[0];
    ++v[1]=s_idCount[1];
    ++v[2]=s_idCount[2];
   // cout<<(float)v[0]/255<<"x "<<(float)v[1]/255<<"y "<<(float)v[2]/255<<"z "<<(float)v[3]/255<<endl;

    return v;
}

void Drawable::Draw(QMatrix4x4 *transform)
{
    // bind my shader to be used
    m_shader->bind();

    // set my uniform color
    m_shader->setUniformValue("color", m_color);

    // calculate and set uniform variable modelMatrix
    m_SceneMatrix = *transform * m_transMatrix;
    m_shader->setUniformValue("modelMatrix", m_modelMatrix);
    m_shader->setUniformValue("sceneMatrix",m_SceneMatrix);
    m_shader->setUniformValue("id",QVector4D((float)m_id[0]/255,(float)m_id[1]/255,(float)m_id[2]/255,(float)m_id[3]/255));
    m_shader->setUniformValue("texture", 0);

    //texture upload

    //bind Texture
    if(m_texture)
        m_texture->bind();

    if(m_isSelected) m_shader->setUniformValue("isSelected", 1.0f);
    else m_shader->setUniformValue("isSelected", 0.0f);
    // draw myself
    m_mesh->Draw();
    m_shader->release();

    // draw my childs
    for(unsigned int i = 0; i < m_childList.size(); ++i) {
        m_childList[i]->Draw(&m_SceneMatrix);
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

void Drawable::SetTexture(QOpenGLTexture *texture){
    m_texture = texture;
}

void Drawable::TranslateDirect(QVector3D transform)
{
    m_modelMatrix.translate(transform);
}

void Drawable::TranslateRelative(QVector3D transform)
{
    QMatrix4x4 translate;
    translate.setToIdentity();
    translate.translate(transform);
    m_transform= translate* m_transform;
    //m_transMatrix.translate(transform);
}

void Drawable::RotateDirect(int deltax,int deltay,int deltaz)
{
    m_modelMatrix.rotate((static_cast<float>(deltax)), QVector3D(1.0f,0.0f,0.0f));
    m_modelMatrix.rotate((static_cast<float>(deltay)), QVector3D(0.0f,1.0f,0.0f));
    m_modelMatrix.rotate((static_cast<float>(deltaz)), QVector3D(0.0f,0.0f,1.0f));
}

void Drawable::TranslateSelectedRelative(QVector3D transform)
{
    m_transform=transform;
    ManipulateSelected();
}

void Drawable::RotateSelectedRelative(int deltax, int deltay, int deltaz){
    xr=deltax;yr=deltay;zr=deltaz;
    ManipulateSelected();
}

void Drawable::scaleSelected(float factor){
    scale_value=factor;
    ManipulateSelected();
}
void Drawable::forceModification(){
    m_manipulateMatrix=m_modelMatrix;
    m_manipulateRMatrix=m_transMatrix;
}

void Drawable::ManipulateSelected(){
    m_transMatrix=m_manipulateRMatrix;
    m_modelMatrix=m_manipulateMatrix;

    m_transMatrix.translate(m_transform);
    m_transMatrix.rotate((static_cast<float>(xr)), QVector3D(1.0f,0.0f,0.0f));
    m_transMatrix.rotate((static_cast<float>(yr)), QVector3D(0.0f,1.0f,0.0f));
    m_transMatrix.rotate((static_cast<float>(zr)), QVector3D(0.0f,0.0f,0.1f));
    m_modelMatrix.scale(scale_value);
}

void Drawable::SetSelected(bool value)
{
    m_isSelected = value;
    if(value){
        m_manipulateMatrix=m_modelMatrix;
        m_manipulateRMatrix=m_transMatrix;
    }
    else{
        m_modelMatrix=m_manipulateMatrix;
        m_transMatrix=m_manipulateRMatrix;
        yr=zr=xr=0;
        scale_value=1.0f;
        m_transform=QVector3D(0.0,0.0,0.0);
    }
}

void Drawable::RotateRelative(float angle, QVector3D axis)
{
    QMatrix4x4 rotate;
    rotate.setToIdentity();
    rotate.rotate(angle, axis);
    m_transMatrix=rotate*m_transMatrix;
    //m_transMatrix.rotate(angle, axis); why?
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


vector<unsigned char> Drawable::GetID()
{
    return m_id;
}

Drawable* Drawable::GetDrawableByID(QVector4D ID)
{
    vector<unsigned char>v(4,255);
    ++v[0]=ID.x()*255;
    ++v[1]=ID.y()*255;
    ++v[2]=ID.z()*255;
    return s_drawableMap.value(v);
}

QMatrix4x4 Drawable::GetSceneMatrix() {
        return m_SceneMatrix;
    }
