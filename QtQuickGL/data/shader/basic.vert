attribute vec4 in_position;
attribute vec4 in_color;

varying vec4 out_position;
varying vec4 out_color;

void main(void)
{
    gl_Position = in_position;

    out_position = in_position;
    out_color = in_color;
}
