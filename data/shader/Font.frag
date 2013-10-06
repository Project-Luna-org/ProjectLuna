#version 120

varying vec2 texture_coordinates;

uniform sampler2D basic_texture;

void main () {
	vec4 texel = texture2D(basic_texture, texture_coordinates);
	gl_FragColor = texel;
}