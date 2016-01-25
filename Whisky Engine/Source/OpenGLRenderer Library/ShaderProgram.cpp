#include "ShaderProgram.h"
#include "..\..\Engine.h"

using std::cout;
using std::endl;

void ShaderProgram::CreateShaderProgram()
{
	program = glCreateProgram();
}

// explanation here: https://youtu.be/6ByZWqPzI70?list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY
bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objPropGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType)
{
	GLint status;
	objPropGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objPropGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;
		delete [] buffer;
		return false;
	}

	return true;
}

bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}
bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

bool ShaderProgram::CreateShader(const char* src, const int type)
{
	std::string source = ResourceManager::Inst()->ReadContents(src);
	const char* code = source.c_str();
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	if (!checkShaderStatus(shader))	return false;

	cout << "\t" << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << " shader compiled successfully." << endl;
	glAttachShader(program, shader);
	return true;
}

bool ShaderProgram::Link()
{
	glLinkProgram(program);
	if (!checkProgramStatus(program))	return false;

	cout << "\tShader Linking successful." << endl;
	return true;
}

void ShaderProgram::Use()
{
	glUseProgram(program);
}

