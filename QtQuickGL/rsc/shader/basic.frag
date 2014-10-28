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
    if(viewMode == 1) { // Normalview
        gl_FragColor.xyz = out_normal.xyz  *0.5 + 0.5;
        gl_FragColor.w = 1.0;
    } else if (viewMode == 2){ // color view
        gl_FragColor = out_color;
    } else if (viewMode == 3) { // position view
        gl_FragColor.xyz = normalize(out_position.xyz)*0.5 + 0.5;
        gl_FragColor.w = 1.0;
    } else if (viewMode == 4) { // id view
        gl_FragColor = id;
    } else if (viewMode == 5) { // texture view
        gl_FragColor = texture2D(texture,out_tcoord);
    } else if (viewMode == 6) { // texture viewcoor
        float x= mod(out_tcoord.x + out_tcoord.y , 0.01)*70.0*mod(out_tcoord.x - out_tcoord.y , 0.01)*70.0;
    gl_FragColor = vec4(x,x,x,1.0);
    }
    else if (viewMode == 7) { // light view
        vec3 ray_norm = normalize(lightPosition-out_position.xyz);
        float k=0.01;
        float dist = distance(lightPosition.xyz, out_position.xyz);

        gl_FragColor.xyz = ray_norm;
        gl_FragColor.w = 1.0 / (k+pow(k*dist,1)+pow(k*dist,2));
    }
    else{ // default view

        // Light calculation

        //gl_FragColor = out_color*texture2D(texture,out_tcoord);
        //gl_FragColor.xyz *= clamp(dot(ray_norm, out_normal.xyz),0.25,1.0);
        //gl_FragColor.xyz /= clamp(pow(distance(out_position.xyz, lightPosition.xyz),2) * 0.0005, 0.5,1.5);

        float ambient_value=1.0;
        float k = 0.009;

        vec4 ambient = vec4(ambient_value, ambient_value, ambient_value, 1.0);
        vec4 ambient_direction = vec4(-1.0,-1.0,1.0,1.0);

        vec3 ray_norm = normalize(lightPosition - out_position.xyz);

        float dist = distance(lightPosition.xyz, out_position.xyz);
        float att = 1.0 / (k + pow(k * dist, 1) + pow(k * dist, 2));

        float dot_normal = clamp(dot(ray_norm, out_normal.xyz), 0.0, 1.0);
        float dot_ambient_normal = clamp(dot(normalize(ambient_direction.xyz), out_normal.xyz), 0.0, 1.0);

        vec4 defuse = out_color * texture2D(texture, out_tcoord);

        gl_FragColor = att * (dot_normal * defuse) + (dot_ambient_normal * defuse * ambient);
        gl_FragColor.w = out_color.w;

        //        gl_FragColor.w = out_color.w;
        //        gl_FragColor.xyz = out_color.xyz
        //                * clamp(dot(ray_norm,out_normal.xyz),0.0,1.0)
        //                / pow(distance(lightPosition.xyz, out_position.xyz),1)
        //                ;

        // Is Selected Case
        gl_FragColor.xyz += 0.05 * isSelected * mod(gl_FragCoord.x + gl_FragCoord.y , 8.0);
    }

    // Draw ID Case
    gl_FragColor.xyz *= 1.0 - isDrawID; // invert
    gl_FragColor.xyz += isDrawID     * id.xyz; // wtf???
}
