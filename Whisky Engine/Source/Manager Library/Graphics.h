// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	Engine.h
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
#ifndef GRAPHICS_H
#define GRAPHICS_H
// C++ headerfiles
#include <unordered_map>
// GLEW headerfiles
#include <glew.h>
// SFML headerfiles
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
// Whisky Engine headerfiles
#include "..\Entity Library\GameObject.h"
#include "..\Component Library\Mesh.h"
#include "..\OpenGLRenderer Library\ShaderProgram.h"

class Graphics
{
	friend class Input;

	typedef std::unordered_map<std::string, GLuint*>	StringMap;
	typedef std::unordered_map<MeshType, GLuint >		MeshTypeMap;

public:
	static Graphics* Inst();

	// system functions
	bool Init();
	bool Load();
	void Render();
	void Unload();
	void Cleanup();

	// window management functions
	void UpdateWindowSize(unsigned int w, unsigned int h);
	unsigned WindowHeight() const	{ return _heigth; }
	unsigned WindowWidth() const	{ return _width; }

	// getter & setter
	const StringMap& Textures() const { return _textures; }	// read-only

	// non-system functions
	void RenderPauseMenu();

private:
	bool CreateQuad();
	bool CreateQuadWireframe();
	bool CreateBoxColliderMesh();

	bool LoadTextures();

	void DrawObject(const GameObject& obj, const glm::mat4 & view, glm::mat4 & proj);
	void DrawDebugMode(const GameObject&);
	void DrawCollider(const GameObject&);

protected:
	sf::RenderWindow* _pWindow;	// window handle
	unsigned _width, _heigth;	// window size
	float _near, _far;
	float _viewAngle;

private:
	static Graphics* _pInstance;

	// system variables
	ShaderProgram _shaderProgram;

	StringMap	_textures;
	MeshTypeMap _meshData;
	glm::mat4 _viewMatrix;
};

#endif