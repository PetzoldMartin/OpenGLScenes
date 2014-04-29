//uniform sampler2D qt_Texture0;
//varying vec4 qt_TexCoord0;

void main(void)
{
    gl_FragColor =  vec4(gl_FragCoord.x / 320.0, gl_FragCoord.y / 480.0, 1.0,1.0);
}
