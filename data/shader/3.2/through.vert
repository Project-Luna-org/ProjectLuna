#version 150 core

uniform mat4 matrix;


in vec3 inVertex;
in vec2 inTextCoords;

out vec2 texture_coordinates;

void main () 
{
	texture_coordinates = inTextCoords;
	gl_Position = matrix * vec4(inVertex,1.0);
}