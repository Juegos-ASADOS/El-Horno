#version 330 core

uniform sampler2D texturaS;
uniform sampler2D texturaM; 
uniform sampler2D texturaC;

in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader

void main() {
	vec3 colorSpace = vec3(texture(texturaS, vUv0)); 
    vec3 colorMetal = vec3(texture(texturaM, vUv0)); 
    vec3 colorChecker = vec3(texture(texturaC, vUv0)); 
	
	if (colorChecker == vec3(1, 1, 1)) 
        fFragColor = vec4(colorMetal, 1.0); 
    else                               
        fFragColor = vec4(colorSpace, 1.0); 
}