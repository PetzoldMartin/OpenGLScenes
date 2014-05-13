attribute vec4 in_position;
attribute vec4 in_color;

varying vec4 out_position;
varying vec4 out_color;

uniform mat4 modelMatrix;
uniform mat4 projMatrix;

void main(void)
{
    gl_Position =  projMatrix * modelMatrix * in_position;

    out_position = in_position;
    out_color = in_color;
}
