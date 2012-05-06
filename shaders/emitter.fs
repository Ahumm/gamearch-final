#version 150

in vec4 v_color;
uniform sampler2D s_tex;

//out vec4 FragColor;

void main() 
{
    //vec4 tex_color = texture(s_tex, gl_PointCoord);
    //gl_FragColor = vec4(v_color.rgb, text_color.a);
    //FragColor = v_color;
    //gl_FragColor = texture2D(s_tex, gl_PointCoord) * v_color;
    gl_FragColor = texture2D(s_tex, gl_PointCoord) * v_color;
    //gl_FragColor = vec4(gl_PointCoord.st, 0, 1);
}