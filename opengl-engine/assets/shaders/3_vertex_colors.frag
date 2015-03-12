#version 330

smooth in vec4 the_color;

out vec4 color_out;

void main() {
	float lerp_value = (gl_FragCoord.x / 1000.0f) + (gl_FragCoord.y / 1300.0f);

	color_out = mix(vec4(the_color.x, the_color.y, the_color.z, the_color.w),
		vec4(0.0f, 0.0f, 0.0f, 0.0f), lerp_value);
}
