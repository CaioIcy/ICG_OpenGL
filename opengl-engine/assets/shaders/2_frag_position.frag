#version 330

out vec4 out_color;

void main() {
	float lerp_value = gl_FragCoord.y / 600.0f;

	out_color = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(0.2f, 0.2f, 0.2f, 0.2f), lerp_value);
}
