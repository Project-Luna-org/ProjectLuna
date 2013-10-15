#version 430 core

layout (location = 0) in vec2 texture_coordinates;
out vec4 outcolor;

uniform sampler2D basic_texture;

void main () 
{
	outcolor = texture(basic_texture, texture_coordinates);
}