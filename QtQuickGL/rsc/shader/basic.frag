varying vec4 out_color;
varying vec4 out_normal;
varying vec4 out_position;
uniform int viewMode;

void main(void)
{
    vec3 ray_norm = normalize(vec3(-3.0,-5.0,7.0));
    vec3 ray_posi = vec3(0.0,0.0,0.0);

    if(viewMode == 1) { // Normalview
        gl_FragColor = out_normal * 0.5 + 0.5;
    } else if (viewMode == 2){ // testview
        gl_FragColor = out_color;
    } else { // default view
        gl_FragColor = out_color;
        gl_FragColor.xyz *= clamp(dot(ray_norm, out_normal.xyz),0.5,1.0);
        gl_FragColor.xyz /= clamp(distance(out_position.xyz, ray_posi) * 0.005, 0.5,1.5);
    }
}
