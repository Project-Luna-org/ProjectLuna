#version 120

uniform mat4 matrix;

attribute vec3 inVertex;

void main () 
{
	
	gl_Position = matrix * vec4(inVertex,1.0);
}