uniform float time;
varying vec4 out_color;

void main(void)
{
    gl_FragColor = out_color * time;
    gl_FragColor.x *= time+1.0;
    gl_FragColor.z += gl_FragColor.y;

}
