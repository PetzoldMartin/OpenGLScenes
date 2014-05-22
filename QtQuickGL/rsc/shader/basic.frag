varying vec4 out_color;
uniform int viewMode;

void main(void)
{
    if(viewMode == 2) {
        gl_FragColor = vec4(gl_FragCoord.w);
    } else {
        gl_FragColor = out_color;
    }
}
