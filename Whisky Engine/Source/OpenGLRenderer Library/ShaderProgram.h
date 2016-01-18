// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	Shader Program.h
// Author			:	Team Stake
// Creation Date	:	2016/1/14
// Purpose			:	Wrapper class for game engine main systems
// History			:
// - 2016/1/14		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

class ShaderProgram
{
public:
	ShaderProgram(){}
	~ShaderProgram(){}

	void CreateShaderProgram();
	bool CreateShader(const char*, const int type);
	bool Link();	
	void Use();
	void Unuse();

	int program;
};

#endif