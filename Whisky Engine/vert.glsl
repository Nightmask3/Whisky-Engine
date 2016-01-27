#version 330

in vec3 vertPosition;
in vec3 vertColor;
in vec3 vertNormal;
//in vec2 texcoords;

out vec3 vPosition;
out vec3 vColor;
out vec3 vNormal;
//out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform bool debug;

uniform vec4 diffuse;

void main()
{
	// for interpolating in fragment shader
	vPosition = vec3(model * vec4(vertPosition, 1.0f));
	vColor = vertColor;
	vNormal = vertNormal;
	//TexCoord = texcoords;

	gl_Position = proj * view * model * vec4(vertPosition, 1.0);	
	
	if(debug)
		;//gl_Position = proj * view * model * vec4(position, 0.01, 1.0);
}