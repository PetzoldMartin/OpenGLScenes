varying vec4 out_color;
varying vec4 out_normal;
varying vec4 out_position;
varying vec2 out_tcoord;

uniform int viewMode;
uniform vec4 cameraPosition;
uniform vec3 lightPosition;
uniform float isDrawID;
uniform float isSelected;
uniform vec4 id;
uniform sampler2D texture;

void main(void)
{
    vec3 ray_norm = normalize(lightPosition-out_position.xyz);


    if(viewMode == 1) { // Normalview
        //gl_FragColor= texture2D(texture,out_tcoord);
        gl_FragColor.xyz = out_normal.xyz  *0.5 + 0.5;
        gl_FragColor.w = 1.0;

    } else if (viewMode == 2){ // color view
        gl_FragColor = out_color;
    } else if (viewMode == 3) { // position view
        gl_FragColor = out_position;
    } else if (viewMode == 4) { // id view
        gl_FragColor = id;
    }else if (viewMode == 5) { // id view
        gl_FragColor= texture2D(texture,out_tcoord);
    }
    else{ // default view

        // Light calculation
        gl_FragColor = out_color;
        gl_FragColor.xyz *= clamp(dot(ray_norm, out_normal.xyz),0.25,1.0);
        gl_FragColor.xyz /= clamp(pow(distance(out_position.xyz, lightPosition.xyz),2) * 0.0005, 0.5,1.5);

        // Is Selected Case
        gl_FragColor.xyz += 0.05 * isSelected * mod(gl_FragCoord.x + gl_FragCoord.y , 8.0);
    }

    // Draw ID Case
    gl_FragColor.xyz *= 1.0 - isDrawID; // invert
    gl_FragColor.xyz += isDrawID     * id.xyz; // wtf???
}
