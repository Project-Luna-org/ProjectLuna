#version 150 core

uniform mat4 matrix;

in vec3 inVertex;

void main () 
{
	
	gl_Position = matrix * vec4(inVertex,1.0);
}