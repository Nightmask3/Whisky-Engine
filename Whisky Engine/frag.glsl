#version 150

in vec3 Color;
in vec2 TexCoord;

out vec4 outColor;

uniform sampler2D tex;
uniform bool debug;
uniform bool collider;

void main()
{
	if(textureSize(tex,0).x>1)
		outColor = texture(tex, TexCoord);
	else
	{
		outColor = vec4(Color, 1.0);
		if(debug)		outColor = vec4(0,1,1,1);
		if(collider)	outColor = vec4(0,1,0,1);
	}
	
}