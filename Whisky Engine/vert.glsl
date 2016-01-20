#version 150

in vec2 position;
in vec3 color;
in vec2 texcoords;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform bool debug;

void main()
{
	Color = color;
	TexCoord = texcoords;

	gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
	if(debug)
		;//gl_Position = proj * view * model * vec4(position, 0.01, 1.0);
}