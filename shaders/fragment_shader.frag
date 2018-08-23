#version 410
out vec4 colour;
uniform vec4 newColour;

void main() 
{
	colour = newColour;
}