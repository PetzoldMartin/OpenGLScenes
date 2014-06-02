varying vec4 out_color;
varying vec4 out_normal;
varying vec4 out_position;

uniform int viewMode;
uniform vec4 cameraPosition;
uniform float isDrawID;
uniform float isSelected;
uniform vec4 id;

void main(void)
{
    vec4 ray_norm = normalize(cameraPosition);
    vec4 ray_posi = -cameraPosition;

    if(viewMode == 1) { // Normalview
        gl_FragColor = out_normal * 0.5 + 0.5;
    } else if (viewMode == 2){ // testview
        gl_FragColor = id;
    } else { // default view

        // Light calculation
        gl_FragColor = out_color;
        gl_FragColor.xyz *= clamp(dot(ray_norm, out_normal),0.5,1.0);
        gl_FragColor.xyz /= clamp(distance(out_position, ray_posi) * 0.005, 0.5,1.5);

        // Is Selected Case
        gl_FragColor.xyz += 0.05 * isSelected * mod(gl_FragCoord.x + gl_FragCoord.y , 8.0);
    }

    // Draw ID Case
    gl_FragColor.xyz *= 1.0 - isDrawID;
    gl_FragColor.xyz += isDrawID     * id.xyz;
}
