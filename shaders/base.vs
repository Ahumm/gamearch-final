#version 150

in vec4 in_Position;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec4 color_through;

void main( void )
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_Position.xyz, 1.0);
	final_color = vec4(0.0,0.0,0.0,1.0);
}
