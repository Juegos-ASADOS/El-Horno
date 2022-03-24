#version 330 core
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader

void main() {
	vec3 color = vec3(1, 1, 1, 1);
	fFragColor = vec4(color, 1.0); // out
}