#version 330

uniform sampler2D tex;
uniform bool debug;
uniform bool collider;

uniform vec4 diffuse;

in vec3 vPosition;
in vec3 vColor;
in vec3 vNormal;

out vec4 outColor;


void main()
{
	// hardcoded values
	vec3 lightPosition = vec3(2, -2, -2);
	vec3 eye = vec3(0, 0, 10);

	vec3 ambient = vec3(1) * 0.25;
	vec3 lightValue = vec3(1.0f, 1.0f, 1.0f)*0.8;
	vec3 specular = vec3(1.0f, 1.0f, 1.0f)*0.2;
	float shininess = 10.0f;

	// lighting calc
	vec3 N = normalize(vNormal);
	vec3 L = normalize(lightPosition - vPosition);
	vec3 V = normalize(eye - vPosition);
	vec3 R = normalize(2*dot(N, L)*N - L);
	vec3 H = normalize(L + V);

	vec3 Kd, Ks, Ka;
	
	/// BRDF
	Kd = lightValue * vec3(diffuse);
	Ks = lightValue * specular;
	Ka = vec3(ambient) * vec3(diffuse);

	vec3 Fresnel 		= Ks + (1-Ks)*pow((1-dot(L,H)), 5);
	float Distribution 	= ((shininess)/(2*3.14159)) * pow(max(0.0, dot(N, H)), shininess);
	float Shadowing		= 1 / pow(dot(L, H), 2);
	vec3 BRDF			= Kd / 3.14159 + Fresnel*Distribution*Shadowing;

	//outColor = vec4(vColor, 1);
	if(dot(N, L) < 0)
		outColor = vec4(BRDF + Ka, 1.0f);
	else
		outColor = vec4(BRDF * max(0.0, dot(N, L)) + Ka, 1.0f);

	/// PHONG
	//Kd = vec3(diffuse) * max(0.0, dot(N, L)) * lightValue;
	//Ks = specular * pow( max(0.0, dot(R, V)) , shininess) * lightValue;
	//Ka = vec3(diffuse) * ambient;

	//outColor = vec4(Kd + Ks + Ka, 1.0f);
}