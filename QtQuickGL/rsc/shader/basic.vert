attribute vec4 in_position;
attribute vec4 in_normal;

varying vec4 out_color;

uniform mat4 modelMatrix;
uniform mat4 projMatrix;
uniform vec4 color;
uniform int viewMode;

void main(void)
{
    gl_Position =  projMatrix * modelMatrix * in_position;

    if(viewMode == 0) {         // Default view
        out_color = color;
    } else if(viewMode == 1) {  // Normal view
        out_color = in_normal * 0.5 + 0.5;
    } else if(viewMode == 2) {
        vec3 cam_pos = (projMatrix * vec4(0.0,0.0,0.0,1.0)).xyz;
        out_color = vec4(distance(gl_Position.xyz, cam_pos)) * 0.000001;
    }







}
