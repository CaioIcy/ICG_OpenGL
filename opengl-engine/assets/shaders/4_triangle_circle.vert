#version 330

layout (location = 0) in vec4 attrib_position;

uniform float time;

void main() {
	float loop_duration = 2.5f;
	float time_scale = 3.1415926535f * 2.0f / loop_duration;
	float current_time = mod(time, loop_duration);

    vec4 total_offset = vec4(
    	cos(current_time * time_scale) * 0.5f,
    	sin(current_time * time_scale) * 0.5f,
    	0.0f,
    	0.0f);
    
    gl_Position = attrib_position + total_offset;
}
