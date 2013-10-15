#version 150 core

in vec2 texture_coordinates;
out vec4 outcolor;

uniform sampler2D basic_texture;

void main () 
{
	outcolor = texture(basic_texture, texture_coordinates);
}