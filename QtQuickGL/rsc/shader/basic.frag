varying vec4 out_color;
varying vec4 out_normal;
varying vec4 out_position;

uniform int viewMode;
uniform vec4 cameraPosition;
uniform float isDrawID;
uniform vec4 id;

void main(void)
{
    vec4 ray_norm = normalize(cameraPosition);
    vec4 ray_posi = -cameraPosition;

    if(viewMode == 1) { // Normalview
        gl_FragColor = out_normal * 0.5 + 0.5;
    } else if (viewMode == 2){ // testview
        gl_FragColor = out_color;
    } else { // default view
        gl_FragColor = out_color;
        gl_FragColor.xyz *= clamp(dot(ray_norm, out_normal),0.5,1.0);
        gl_FragColor.xyz /= clamp(distance(out_position, ray_posi) * 0.005, 0.5,1.5);
    }

    //gl_FragColor.xyz *= 1.0 - isDrawID;
    //gl_FragColor.xyz += isDrawID * id;

    gl_FragColor.xyz *= 1.0 - isDrawID;
    gl_FragColor.xyz += isDrawID     * id.xyz;
}
