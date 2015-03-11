#version 330

layout (location = 0) in vec4 attrib_position;
layout (location = 1) in vec4 attrib_color;

smooth out vec4 the_color;

void main() {
	gl_Position = attrib_position;
	the_color = attrib_color;
}
