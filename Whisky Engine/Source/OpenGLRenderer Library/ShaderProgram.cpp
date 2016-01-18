#include "ShaderProgram.h"
#include "..\..\Engine.h"

using std::cout;
using std::endl;

void ShaderProgram::CreateShaderProgram()
{
	program = glCreateProgram();
}

//////// TODO: Status refactoring
// function for checking compilation and link errors
// to understand whats going on: https://youtu.be/6ByZWqPzI70?t=6m54s
bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objPropGetter, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType)
{
	GLint status;
	objPropGetter(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objPropGetter(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;
		delete [] buffer;
		return false;
	}

	return true;
}

// TODO: implement stuff
bool checkShaderStatus(GLuint shaderID)
{
	return true;
}

// TODO: implement stuff
bool checkProgramStatus(GLuint programID)
{
	return true;
}
//////// END of refactor

bool ShaderProgram::CreateShader(const char* src, const int type)
{
	std::string source = ResourceManager::Inst()->ReadContents(src);
	const char* code = source.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	// check for compilation errors (may use checkStatus())
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		cout << "Error compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << src << endl << source
			<< endl << buffer << endl;

		return false;
	}

	cout << "\t" << ((type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment") << " shader compiled successfully." << endl;
	glAttachShader(program, shader);
	return true;
}

bool ShaderProgram::Link()
{
	// link the shader program
	glLinkProgram(program);
	
	// check link status (may use checkStatus())
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		char buffer[512];
		glGetProgramInfoLog(program, 512, NULL, buffer);
		cout << "Error linking shaders: " << endl << buffer << endl;
		return false;;
	}

	cout << "\tShader Linking successful." << endl;
	return true;
}

void ShaderProgram::Use()
{
	glUseProgram(program);
}

