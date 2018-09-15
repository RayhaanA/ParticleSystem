#version 410
out vec4 fragColour;
//uniform vec4 newColour;
in vec4 colour;

void main() 
{
	fragColour = colour;
}