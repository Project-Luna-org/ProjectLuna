#version 430 core

uniform mat4 matrix;

layout (location = 0) in vec3 inVertex;

void main () 
{
	
	gl_Position = matrix * vec4(inVertex,1.0);
}