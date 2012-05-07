#version 150

in vec4 v_color;
uniform sampler2D s_tex;

void main() 
{
    vec4 tex_color = texture2D(s_tex, gl_PointCoord);
    gl_FragColor = vec4(v_color.rgb, min(tex_color.a, v_color.a));
}