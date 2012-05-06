#version 150

in vec3 in_Position;
in vec4 in_Color;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform float uThickness;

out vec4 v_color;

void main() {
    v_color = in_Color;
    gl_PointSize = uThickness;
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_Position.xyz, 1.0) * 3.0f;
}