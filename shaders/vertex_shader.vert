#version 410
layout (location = 0) in vec3 vp;
layout (location = 1) in mat4 model;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 m;

void main() {
	gl_Position =  projection * view * m * vec4(vp, 1.0);
}