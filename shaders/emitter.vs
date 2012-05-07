#version 150
#define win_height 1200
#define win_width 675
#define sprite_size 32

in vec3 in_Position;
in vec4 in_Color;

uniform mat4 MVPMatrix;
uniform vec3 cam_pos;
uniform float uThickness;

out vec4 v_color;

void main() {
	vec4 pos = MVPMatrix * vec4(in_Position.xyz, 1.0);
	vec4 c_pos = MVPMatrix * vec4(cam_pos.xyz, 1.0);
	
	float d = distance(vec3(pos.xyz), vec3(c_pos.xyz));
	float point_size = win_height / (d * d);
	
    v_color = in_Color;
    gl_PointSize = point_size * (1 / uThickness);
    //gl_PointSize = uThickness;
    gl_Position = MVPMatrix * vec4(in_Position.xyz, 1.0) * 3.0f;
}