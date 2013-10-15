#version 430 core

uniform mat4 matrix;


layout (location = 0) in vec3 inVertex;
layout (location = 1) in vec2 inTextCoords;

out vec2 texture_coordinates;

void main () 
{
	texture_coordinates = inTextCoords;
	gl_Position = matrix * vec4(inVertex,1.0);
}