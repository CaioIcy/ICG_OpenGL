#version 330

layout (location = 0) in vec3 atb_position;
layout (location = 1) in vec4 atb_color;

uniform mat4 full_transform_matrix;

out vec4 sh_color;

void main() {
	vec4 v = vec4(atb_position.x, atb_position.y, atb_position.z, 1.0f);
	vec4 projected_position = full_transform_matrix * v;
	gl_Position = projected_position;
	sh_color = atb_color;
}
