// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	Engine.h
// Author			:	Team Stake
// Creation Date	:	2016/1/14
// Purpose			:	Rendering
// History			:
// - 2016/1/14		:	- initial implementation
//
// Copyright(C) 2015 DigiPen Institute of Technology.
// Reproduction or disclosure of this file or its contents without the prior written
// consent of DigiPen Institute of Technology is prohibited.
// ---------------------------------------------------------------------------

// C++ header files
#include <sstream>

// Whisky Engine header files
#include "Graphics.h"
#include "..\..\Engine.h"
#include "..\..\Dependencies\glm\glm\gtc\matrix_transform.hpp"
#include "..\..\Dependencies\glm\glm\gtc\type_ptr.hpp"
#include "..\Component Library\CameraComponent.h"

using std::cout;
using std::endl;
using std::string;

#define DEBUG1

// Debugging tool: http://www.gremedy.com/


//const GLuint NUM_VERT_PER_TRI = 3;
//const GLuint NUM_FLOAT_PER_VERT = 3;
//const GLuint TRI_SIZE = NUM_VERT_PER_TRI * NUM_FLOAT_PER_VERT * sizeof(float);
//
//struct Vertex
//{
//	glm::vec3 position;
//	glm::vec3 color;
//};

////////////////////////////////////////////////////////////////
//		System Functions
////////////////////////////////////////////////////////////////

Graphics* Graphics::pInstance_ = NULL;

Graphics* Graphics::Inst()
{
	if (pInstance_ == NULL) pInstance_ = new Graphics();
	return pInstance_;
}

bool Graphics::Init()
{
	// Amazing OpenGL tutorial: https://open.gl/context

	std::ostringstream os;
	os << "WhiskyEngine v" << Engine::Version() << " | To The Light v0.1";
	string label = os.str();

	// create the window
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 2;
	settings.majorVersion = 3;

	// Width and height of window
	width_ = Engine::_resolution_w;
	heigth_ = Engine::_resolution_h;

	pWindow_ = new sf::RenderWindow(sf::VideoMode(width_, heigth_), label, sf::Style::Default, settings);
	if (!pWindow_)
	{
		cout << "Error creating window" << endl;
		return false;
	}

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// print system info
	cout << "Graphics System initialized.\n";
	cout << "\tOpenGL Settings" << endl;
	cout << "\tdepth bits:\t\t" << settings.depthBits << endl;
	cout << "\tstencil bits:\t\t" << settings.stencilBits << endl;
	cout << "\tantialiasing level:\t" << settings.antialiasingLevel << endl;
	cout << "\tversion:\t\t" << settings.majorVersion << "." << settings.minorVersion << endl << endl;
	return true;
}

bool Graphics::Load()
{
	cout << "Graphics System Loading..." << endl;

	// --------------------------------------------------------
	//	Shaders
	// --------------------------------------------------------
	auto vert = "vert.glsl";
	auto frag = "frag.glsl";
	shaderProgram_.CreateShaderProgram();
	if (!shaderProgram_.CreateShader(vert, GL_VERTEX_SHADER))	return false;
	if (!shaderProgram_.CreateShader(frag, GL_FRAGMENT_SHADER))	return false;
	if (!shaderProgram_.Link())									return false;
	shaderProgram_.Use();

	// --------------------------------------------------------
	//	Geometry 
	// --------------------------------------------------------
	if (//!CreateTriangle() ||
		!CreateCubeMesh()
		)
		return false;


	// --------------------------------------------------------
	//	Textures
	// --------------------------------------------------------
	//if (!LoadTextures()) return false;

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);

	// print system info
	cout << "Graphics System Loaded." << endl;
	return true;
}

void Graphics::Render()
{
	// Clear the screen to gray
	glViewport(0, 0, width_, heigth_);
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Get the View & Projection matrices
	glm::mat4 vProj = GOM->GetCamera()->GetComponent<CameraComponent>()->GetProjectionMatrix();
	
	// View matrix settings
	glm::vec3 eye = GOM->GetCamera()->GetComponent<Transform>()->GetPosition();
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);  //glm::vec3 target = GOM->GetPlayer()->GetComponent<Transform>()->GetPosition(); // Switch to this when we have a way of specifying the player properly!!!
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	// Creation of view matrix (default view, can be overridden)
	_viewMatrix = glm::lookAt(eye, target, up);
	//_viewMatrix = glm::mat4(1);

	// draw active objects with active mesh components
	for (auto& obj : GOM->GameObjList())
	{
		if (obj.IsActive() && obj.GetComponent<Mesh>() && obj.GetComponent<Mesh>()->IsActive())
			DrawObject(obj, _viewMatrix, vProj);
	}

	// swap buffers
	pWindow_->display();
}

void Graphics::Unload()
{
	for (auto it = textures_.begin(); it != textures_.end(); ++it)
		delete it->second;

	cout << "Graphics System unloaded." << endl;
}

void Graphics::Cleanup()
{
	if (pWindow_)	delete pWindow_;
	cout << "Graphics System cleaned up.\n";
}

////////////////////////////////////////////////////////////////
//		Draw Functions
////////////////////////////////////////////////////////////////

void Graphics::DrawDebugMode(const GameObject& obj)
{
	// set vao					// can also be acquired from obj if tied during construction
	glBindVertexArray(meshData_[MeshType::QUAD_WIREFRAME]);

	GLint debug = glGetUniformLocation(shaderProgram_.program, "debug");
	glUniform1i(debug, true);

	// Draw call
	glDrawElements(GL_LINES, 10, GL_UNSIGNED_INT, 0);

	// cleanup
	glUniform1i(debug, false);
	glBindVertexArray(0);
}

//void Graphics::DrawCollider(const GameObject& obj)
//{
//	// set vao					// can also be acquired from obj if tied during construction
//	glBindVertexArray(_meshData[MeshType::BOX_COLLIDER_MESH]);
//
//	glm::vec3 pos = obj.GetComponent<BoxCollider2D>()->Center();
//	glm::vec3 rot = obj.GetComponent<BoxCollider2D>()->Orientation();
//	glm::vec3 scale = obj.GetComponent<BoxCollider2D>()->Scale();
//
//	Matrix3D vModel = mat4::Translate(pos) *
//		mat4::Rotate(2, rot*DEG2RAD) *
//		mat4::Scale(scale);
//
//	// send shader parameters
//	GLint uniTrans = glGetUniformLocation(shaderProgram_.program, "model");
//	glUniformMatrix4fv(uniTrans, 1, GL_TRUE, vModel.Pntr());
//
//	GLint collider = glGetUniformLocation(shaderProgram_.program, "collider");
//	glUniform1i(collider, true);
//
//	// Draw call
//	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
//
//	// cleanup
//	glUniform1i(collider, false);
//	glBindVertexArray(0);
//}

void Graphics::DrawObject(const GameObject& obj, const glm::mat4 & vView, const glm::mat4 & vProj)
{
	glBindVertexArray(meshData_[obj.GetComponent<Mesh>()->Type()]);
	// assert dereference stuff maybe?

	glm::mat4 vModel = obj.GetComponent<Transform>()->ModelTransformationMatrix();
	glm::vec4 color = obj.GetComponent<Mesh>()->GetColor().Value();

	// send shader parameters
	GLint loc;	// uniform location

	loc = glGetUniformLocation(shaderProgram_.program, "model");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(vModel));

	loc = glGetUniformLocation(shaderProgram_.program, "view");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(vView));

	loc = glGetUniformLocation(shaderProgram_.program, "proj");
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(vProj));

	loc = glGetUniformLocation(shaderProgram_.program, "diffuse");
	glUniform4fv(loc, 1, &color[0]);	// vec4

	// Draw call
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	// cleanup
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glBindVertexArray(0);

	//// debug draws // EDIT : DEACTIVATED FOR NOW WHILE REFACTORING, REIMPLEMENT 
	//if (Engine::_debugDraw)	DrawDebugMode(obj);
	//if (Engine::_debugDraw && obj.GetComponent<BoxCollider2D>() != NULL)
	//	DrawCollider(obj);

}

void Graphics::RenderPauseMenu()
{
	glm::mat4 proj, view;
	GameObject* obj = GOM->GetMenu();

	if (!obj) return;
	GFX->DrawObject(*obj, view, proj);
	pWindow_->display();
}

// load functions
//bool Graphics::LoadTextures()
//{
//	//auto textureFiles = RSC::Inst()->GetTextureFiles();
//	//glGenTextures(texCount, textures_);
//	int i = 0;
//	for (auto path : textureFiles)
//	{
//		GLuint* p = new GLuint;
//		glGenTextures(1, p);
//		textures_[path] = p;
//		glBindTexture(GL_TEXTURE_2D, *p);
//
//		sf::Image img;
//		if (!img.loadFromFile(path))
//		{
//			cout << "Error loading texture from file: " << path << endl;
//			return false;
//		}
//
//		// enable alpha blending
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glTexImage2D(
//			GL_TEXTURE_2D, 0, GL_RGBA,
//			img.getSize().x, img.getSize().y,
//			0,
//			GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr()
//			);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glBindTexture(GL_TEXTURE_2D, 0);
//	}
//
//	return true;
//}

////////////////////////////////////////////////////////////////
//		Geometry Functions
////////////////////////////////////////////////////////////////

bool Graphics::CreateTriangle()
{
	MeshData tri = MeshGenerator::MakeTriangle();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	meshData_[MeshType::QUAD] = vbo;	// register buffer ID for the mesh type

	/////////////////////////////////////////////////////////////////////////
	/// VERTEX DATA
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, tri.vertexBufferSize(), tri.vertices, GL_STATIC_DRAW);

	GLsizei stride = sizeof(float) * 6;		// (24B) 6 floats per vertex data (3pos, 3color)
	const void* offset = (void*)(sizeof(float) * 3);	// (12B) offset position (3 floats)

	GLint index = glGetAttribLocation(shaderProgram_.program, "vertPosition");
	glEnableVertexAttribArray(index);	
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, 0);		// 3 floats for position
	//							 ^-----------------------------------------+
	index = glGetAttribLocation(shaderProgram_.program, "vertColor");
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, offset); // 3 floats for color
	//							 ^------------------------------------------+
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	/////////////////////////////////////////////////////////////////////////
	// ELEMENT DATA
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri.indexBufferSize(), tri.indices, GL_STATIC_DRAW);
	
	tri.CleanUp();
	return true;
}

bool Graphics::CreateCubeMesh()
{
	MeshData cube = MeshGenerator::MakeCube();

	GLuint vbo;
	glGenBuffers(1, &vbo);
	meshData_[MeshType::CUBE] = vbo;	// register buffer ID for the mesh type

	/////////////////////////////////////////////////////////////////////////
	/// VERTEX DATA
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize(), cube.vertices, GL_STATIC_DRAW);

	GLsizei stride = sizeof(float) * 6;		// (24B) 6 floats per vertex data (3pos, 3color)
	const void* offset = (void*)(sizeof(float) * 3);	// (12B) offset position (3 floats)

	GLint index = glGetAttribLocation(shaderProgram_.program, "vertPosition");
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, 0);		// 3 floats for position
	//							 ^-----------------------------------------+
	index = glGetAttribLocation(shaderProgram_.program, "vertColor");
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, offset); // 3 floats for color
	//							 ^------------------------------------------+
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	/////////////////////////////////////////////////////////////////////////
	// ELEMENT DATA
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indexBufferSize(), cube.indices, GL_STATIC_DRAW);

	cube.CleanUp();
	return true;
}

//bool Graphics::CreateQuadWireframe()
//{
//	//	Vertex Array Object
//	GLuint vao;
//	glGenVertexArrays(1, &vao);
//
//	meshData_[MeshType::QUAD_WIREFRAME] = vao;
//
//	glBindVertexArray(vao);
//	float vertices[] =
//	{//   X      Y      
//		-0.5f, +0.5f,  	// Top-left
//		+0.5f, +0.5f, 	// Top-right
//		+0.5f, -0.5f, 	// Bottom-right
//		-0.5f, -0.5f, 	// Bottom-left
//	};
//
//	GLuint elements[] = {
//		0, 1,
//		1, 2,
//		2, 0,
//		2, 3,
//		3, 0
//	};
//
//	//////////////////////////////////////////////////////////
//
//	// activate & send data to the buffer
//	GLuint vbo;
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);						// static: upload once draw many times
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	//	Element Buffer Object
//	GLuint ebo;
//	glGenBuffers(1, &ebo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
//
//	//	Shader Parameters
//	// attributes
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	GLint posAttrib = glGetAttribLocation(shaderProgram_.program, "position");	// handle to vert shader argument
//	glEnableVertexAttribArray(posAttrib);
//	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
//		2 * sizeof(float), 0); // how to interpret input array
//	// position, vec2, type, normalize mode, stride, offset
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// check for errors
//	int err;
//	if ((err = glGetError()) != 0)
//	{
//		cout << "Error(" << err << ") | Graphics : CreateQuadWireframe" << endl;
//		return false;
//	}
//
//	return true;
//}
//
//bool Graphics::CreateBoxColliderMesh()
//{
//	//	Vertex Array Object
//	GLuint vao;
//	glGenVertexArrays(1, &vao);
//
//	meshData_[MeshType::BOX_COLLIDER_MESH] = vao;
//
//	glBindVertexArray(vao);
//	float vertices[] =
//	{//   X      Y      
//		-0.5f, +0.5f,  	// Top-left
//		+0.5f, +0.5f, 	// Top-right
//		+0.5f, -0.5f, 	// Bottom-right
//		-0.5f, -0.5f, 	// Bottom-left
//	};
//
//	GLuint elements[] = {
//		0, 1,
//		1, 2,
//		2, 3,
//		3, 0
//	};
//
//	//////////////////////////////////////////////////////////
//
//	// activate & send data to the buffer
//	GLuint vbo;
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);						// static: upload once draw many times
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	//	Element Buffer Object
//	GLuint ebo;
//	glGenBuffers(1, &ebo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
//
//	//	Shader Parameters
//	// attributes
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	GLint posAttrib = glGetAttribLocation(shaderProgram_.program, "position");	// handle to vert shader argument
//	glEnableVertexAttribArray(posAttrib);
//	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
//		2 * sizeof(float), 0); // how to interpret input array
//	// position, vec2, type, normalize mode, stride, offset
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// check for errors
//	int err;
//	if ((err = glGetError()) != 0)
//	{
//		cout << "Error(" << err << ") | Graphics : CreateBoxCollider" << endl;
//		return false;
//	}
//
//	return true;
//}
