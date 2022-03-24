#version 330 core
in vec4 vertex; // atributos de los vértices a procesar
in vec2 uv0; // coordenadas de textura 0
uniform mat4 modelViewProjMat; // constante de programa
out vec2 vUv0; // out del vertex shader

void main() {
	vUv0 = uv0; // se pasan las coordenadas de textura
	gl_Position = modelViewProjMat * vertex; //obligatorio
}