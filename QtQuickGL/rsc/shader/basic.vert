attribute vec4 in_position;
attribute vec4 in_normal;

varying vec4 out_color;

uniform mat4 modelMatrix;
uniform mat4 projMatrix;
uniform vec4 color;

void main(void)
{
    gl_Position =  projMatrix * modelMatrix * in_position;
    out_color = color;
}
