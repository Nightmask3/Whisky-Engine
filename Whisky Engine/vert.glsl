#version 330

in vec3 vertPosition;
in vec3 vertColor;
in vec3 vertNormal;
//in vec2 texcoords;

out vec3 vPosition;
out vec3 vColor;
out vec3 vNormal;
//out vec2 TexCoord;

out vec3 eyeVector; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform bool debug;

uniform vec4 diffuse;

void main()
{
	// hardcoded values
	vec3 lightPos = vec3(0, 5, 0);	// right above the camera
	vec3 eyePos = vec3(0, 0, 10);		// camera position
	
	vec3 worldPos = vec3(model * vec4(vertPosition, 1.0f));

	vec3 eyeVector = eyePos - worldPos;

	// for interpolating in fragment shader
	vPosition = worldPos;
	vColor = vertColor;
	vNormal = vertNormal;
	//TexCoord = texcoords;

	gl_Position = proj * view * model * vec4(vertPosition, 1.0);	
	
	if(debug)
		;//gl_Position = proj * view * model * vec4(position, 0.01, 1.0);
}