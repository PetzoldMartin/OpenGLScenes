attribute vec4 in_position;
attribute vec4 in_normal;

varying vec4 out_color;
varying vec4 out_normal;
varying vec4 out_position;

uniform mat4 modelMatrix;
uniform mat4 projMatrix;
uniform vec4 color;
uniform vec4 id;
uniform float isDrawID;
uniform int viewMode;
uniform mat4 sceneMatrix;

void main(void)
{
    gl_Position =  projMatrix * sceneMatrix * modelMatrix * in_position;
    out_color = color;
    out_normal = normalize(sceneMatrix * modelMatrix* in_normal);
    out_position = in_position;
}
