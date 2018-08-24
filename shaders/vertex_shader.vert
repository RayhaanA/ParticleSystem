#version 410
in vec3 vp;
uniform mat4 mvp;

void main() {
	gl_Position = mvp * vec4(vp, 1.0);
}