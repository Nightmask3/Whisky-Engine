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

// C++ header files
#include <unordered_map>

// GLEW header files
#include <glew.h>

// SFML header files
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

// Whisky Engine header files
#include "..\Entity Library\GameObject.h"
#include "..\Component Library\Mesh.h"
#include "..\OpenGLRenderer Library\ShaderProgram.h"
#include "..\OpenGLRenderer Library\MeshData.h"
#include "..\OpenGLRenderer Library\MeshGenerator.h"

class Graphics
{
	friend class Input;

	typedef std::unordered_map<std::string, GLuint*>	TextureMap;
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
	void UpdateWindowSize(unsigned int w, unsigned int h) { width_ = w; heigth_ = h; }
	unsigned WindowHeight() const	{ return heigth_; }
	unsigned WindowWidth() const	{ return width_; }

	// getters & setters
	const TextureMap& Textures() const { return textures_; }	// read-only

	// pause-menu exception (its sort of a hack tho)
	void RenderPauseMenu();

private:
	// built in geometry
	//bool CreateQuad();
	//bool CreateQuadWireframe();
	//bool CreateBoxColliderMesh();
	bool CreateTriangle();
	bool CreateCubeMesh();

	bool LoadTextures();

	// draw functions
	void DrawObject(const GameObject& obj, const glm::mat4 & view, const glm::mat4 & proj);
	void DrawDebugMode(const GameObject&);
	void DrawCollider(const GameObject&);

protected:
	sf::RenderWindow* pWindow_;	// window handle
	unsigned width_, heigth_;	// window size

private:
	static Graphics* pInstance_;

	// system variables
	ShaderProgram shaderProgram_;

	TextureMap	textures_;
	MeshTypeMap meshData_;
		
	glm::mat4 _viewMatrix; 
};

#endif