attribute vec4 in_position;
attribute vec4 in_normal;

varying vec4 out_color;
varying vec4 out_normal;
varying vec4 out_position;

uniform mat4 modelMatrix;
uniform mat4 projMatrix;
uniform vec4 color;
uniform int viewMode;

void main(void)
{
    gl_Position =  projMatrix * modelMatrix * in_position;

    out_color = color;
    out_normal = in_normal;
    out_position = gl_Position;
}
