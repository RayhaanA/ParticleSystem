#version 410
layout (location = 0) in vec3 vp;
layout (location = 1) in mat4 modelInstance;
layout (location = 5) in vec4 colourInstance;
out vec4 colour;

uniform mat4 projection;
uniform mat4 view;
//uniform mat4 m;

void main() {
	gl_Position =  projection * view * modelInstance * vec4(vp, 1.0);
	colour = colourInstance;
}