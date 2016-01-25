#version 150

in vec3 vertPosition;
in vec3 vertColor;
//in vec2 texcoords;

out vec3 vColor;
//out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform bool debug;

uniform vec4 diffuse;

void main()
{
	vColor = vertColor;
	//TexCoord = texcoords;

	gl_Position = proj * view * model * vec4(vertPosition, 1.0);
	
	if(debug)
		;//gl_Position = proj * view * model * vec4(position, 0.01, 1.0);
}