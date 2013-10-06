#version 120

uniform mat4 matrix;

varying vec2 texture_coordinates;

attribute vec3 inVertex;
attribute vec2 inTextCoords;

void main () 
{
	texture_coordinates = inTextCoords;
	gl_Position = matrix * vec4(inVertex,1.0);
}