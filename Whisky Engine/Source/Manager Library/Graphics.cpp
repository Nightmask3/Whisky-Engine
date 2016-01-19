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

// C++ headerfiles
#include <sstream>
// Whisky Engine headerfiles
#include "Graphics.h"
#include "..\..\Engine.h"
#include "..\Math Library\Matrix3D.h"
#include "..\Math Library\Vector3D.h"

using std::cout;
using std::endl;
using std::string;


#define DEBUG1

// Debugging tool: http://www.gremedy.com/


Graphics* Graphics::_pInstance = NULL;

Graphics* Graphics::Inst()
{
	if (_pInstance == NULL) _pInstance = new Graphics();
	return _pInstance;
}

bool Graphics::Init()
{
	// Amazing OpenGL tutorial: https://open.gl/context

	std::ostringstream os;
	os << "Engine v" << Engine::Version() << " | To The Light v0.1";
	string label = os.str();

	// create the window
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 2;
	settings.majorVersion = 3;
	// Width and height of window
	_width = Engine::_resolution_w;
	_heigth = Engine::_resolution_h;

	_pWindow = new sf::RenderWindow(sf::VideoMode(_width, _heigth), label, sf::Style::Default, settings);
	if (!_pWindow)
	{
		cout << "Error creating window" << endl;
		return false;
	}

	// Perspective matrix settings
	_near = 1.0f;
	_far = 100.0f;
	_viewAngle = 45.0f;
	// View matrix settings
	Vector3D eye(0.0f, 10.0f, -10.0f, 0.0f);
	Vector3D target(0.0f, 0.0f, 1.0f, 0.0f);
	Vector3D up(0.0f, 1.0f, 0.0f, 0.0f);

	// Creation of view matrix (default view, can be overriden)
	_viewMatrix = CreateViewMatrix(eye, target, up);

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
// load functions
bool Graphics::LoadTextures()
{
	auto textureFiles = RSC::Inst()->GetTextureFiles();
	//glGenTextures(texCount, _textures);
	int i = 0;
	for (auto path : textureFiles)
	{
		GLuint* p = new GLuint;
		glGenTextures(1, p);
		_textures[path] = p;
		glBindTexture(GL_TEXTURE_2D, *p);

		sf::Image img;
		if (!img.loadFromFile(path))
		{
			cout << "Error loading texture from file: " << path << endl;
			return false;
		}

		// enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA,
			img.getSize().x, img.getSize().y,
			0,
			GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr()
			);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	return true;
}

bool Graphics::CreateQuad()
{
	//	Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);

	_meshData[MeshType::QUAD] = vao;

	glBindVertexArray(vao);
	float vertices[] =
	{//   X      Y       R     G     B	 S	   T
		-0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,		// Top-left
		+0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,		// Top-right
		+0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,		// Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,		// Bottom-left
	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};


	//	Vertex Buffer Object
	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

	// activate & send data to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);						// static: upload once draw many times
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//	Element Buffer Object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//	Shader Parameters
	// attributes
	GLint posAttrib = glGetAttribLocation(_shaderProgram.program, "position");	// handle to vert shader argument
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
		7 * sizeof(float), 0); // how to interpret input array
	// position, vec2, type, normalize mode, stride, offset

	GLint colAttrib = glGetAttribLocation(_shaderProgram.program, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
		7 * sizeof(float), (void*)(2 * sizeof(float)));

	GLint texAttrib = glGetAttribLocation(_shaderProgram.program, "texcoords");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
		7 * sizeof(float), (void*)(5 * sizeof(float)));

	// check for errors
	int err;
	if ((err = glGetError()) != 0)
	{
		cout << "Error(" << err << ") | Graphics : CreateQuad" << endl;
		return false;
	}

	return true;
}

bool Graphics::CreateQuadWireframe()
{
	//	Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);

	_meshData[MeshType::QUAD_WIREFRAME] = vao;

	glBindVertexArray(vao);
	float vertices[] =
	{//   X      Y      
		-0.5f, +0.5f,  	// Top-left
		+0.5f, +0.5f, 	// Top-right
		+0.5f, -0.5f, 	// Bottom-right
		-0.5f, -0.5f, 	// Bottom-left
	};

	GLuint elements[] = {
		0, 1,
		1, 2,
		2, 0,
		2, 3,
		3, 0
	};

	//////////////////////////////////////////////////////////

	// activate & send data to the buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);						// static: upload once draw many times
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//	Element Buffer Object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//	Shader Parameters
	// attributes
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint posAttrib = glGetAttribLocation(_shaderProgram.program, "position");	// handle to vert shader argument
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
		2 * sizeof(float), 0); // how to interpret input array
	// position, vec2, type, normalize mode, stride, offset
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// check for errors
	int err;
	if ((err = glGetError()) != 0)
	{
		cout << "Error(" << err << ") | Graphics : CreateQuadWireframe" << endl;
		return false;
	}

	return true;
}

bool Graphics::CreateBoxColliderMesh()
{
	//	Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);

	_meshData[MeshType::BOX_COLLIDER_MESH] = vao;

	glBindVertexArray(vao);
	float vertices[] =
	{//   X      Y      
		-0.5f, +0.5f,  	// Top-left
		+0.5f, +0.5f, 	// Top-right
		+0.5f, -0.5f, 	// Bottom-right
		-0.5f, -0.5f, 	// Bottom-left
	};

	GLuint elements[] = {
		0, 1,
		1, 2,
		2, 3,
		3, 0
	};

	//////////////////////////////////////////////////////////

	// activate & send data to the buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);						// static: upload once draw many times
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//	Element Buffer Object
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//	Shader Parameters
	// attributes
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLint posAttrib = glGetAttribLocation(_shaderProgram.program, "position");	// handle to vert shader argument
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
		2 * sizeof(float), 0); // how to interpret input array
	// position, vec2, type, normalize mode, stride, offset
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// check for errors
	int err;
	if ((err = glGetError()) != 0)
	{
		cout << "Error(" << err << ") | Graphics : CreateBoxCollider" << endl;
		return false;
	}

	return true;
}

bool Graphics::Load()
{
	cout << "Graphics System Loading..." << endl;
	// --------------------------------------------------------
	//	Vertex & Fragment Shaders
	// --------------------------------------------------------
	_shaderProgram.CreateShaderProgram();
	_shaderProgram.CreateShader("vert.glsl", GL_VERTEX_SHADER);
	_shaderProgram.CreateShader("frag.glsl", GL_FRAGMENT_SHADER);

	glBindFragDataLocation(_shaderProgram.program, 0, "outColor");	// not necessary for only 1 output

	_shaderProgram.Link();
	_shaderProgram.Use();
	// check for errors
	int err;
	if ((err = glGetError()) != 0)
	{
		cout << "Error(" << err << ") graphics loading!" << endl;
		return false;
	}

	// --------------------------------------------------------
	//	Geometry 
	// --------------------------------------------------------
	if (!CreateQuad() ||
		!CreateQuadWireframe() ||
		!CreateBoxColliderMesh()
		)
		return false;


	// --------------------------------------------------------
	//	Textures
	// --------------------------------------------------------
	if (!LoadTextures()) return false;

	// print system info
	cout << "Graphics System Loaded." << endl;
	return true;
}

void Graphics::DrawDebugMode(const GameObject& obj)
{
	// set vao					// can also be acquired from obj if tied during construction
	glBindVertexArray(_meshData[MeshType::QUAD_WIREFRAME]);

	GLint debug = glGetUniformLocation(_shaderProgram.program, "debug");
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


	//	Vector3D pos	= obj.GetComponent<BoxCollider2D>()->Center();
	//	float rot	= obj.GetComponent<BoxCollider2D>()->Orientation();
	//	Vector3D scale	= obj.GetComponent<BoxCollider2D>()->Scale();

	//	Matrix3D vModel = mat4::Translate(pos) *
	//		mat4::Rotate(2, rot*DEG2RAD) *
	//		mat4::Scale(scale);

	//	// send shader parameters
	//	GLint uniTrans = glGetUniformLocation(_shaderProgram.program, "model");
	//	glUniformMatrix4fv(uniTrans, 1, GL_TRUE, vModel.Pntr());

	//	GLint collider = glGetUniformLocation(_shaderProgram.program, "collider");
	//	glUniform1i(collider, true);

	//	// Draw call
	//	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);

	//	// cleanup
	//	glUniform1i(collider, false);
	//	glBindVertexArray(0);
	//}

void Graphics::DrawObject(const GameObject& obj, const Matrix3D & vView, const Matrix3D & vProj)
{
	glBindVertexArray(_meshData[obj.GetComponent<Mesh>()->MeshHandle()]);
	// assert dereference stuff maybe?

	Matrix3D vModel = obj.GetComponent<Transform>()->ModelTransformationMatrix();

	// send shader parameters
	GLint uniTrans = glGetUniformLocation(_shaderProgram.program, "model");
	glUniformMatrix4fv(uniTrans, 1, GL_TRUE, vModel.Pntr());

	GLint uniView = glGetUniformLocation(_shaderProgram.program, "view");
	glUniformMatrix4fv(uniView, 1, GL_TRUE, vView.Pntr());

	GLint uniProj = glGetUniformLocation(_shaderProgram.program, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_TRUE, vProj.Pntr());

	Sprite* sprite = obj.GetComponent<Sprite>();
	if (sprite != NULL){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, *sprite->Texture());
		GLint tex = glGetUniformLocation(_shaderProgram.program, "tex");
		glUniform1i(tex, 0);
	}

	// Draw call
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// cleanup
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	//// debug draws // EDIT : DEACTIVATED FOR NOW WHILE REFACTORING, REIMPLEMENT 
	//if (Engine::_debug)	DrawDebugMode(obj);
	//if (Engine::_debug && obj.GetComponent<BoxCollider2D>() != NULL)
	//	DrawCollider(obj);

}

void Graphics::Render()
{
	// Clear the screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	Matrix3D vProj = CreateProjectionMatrix(_viewAngle, (float)_width / _heigth, _near, _far);
	
	//Matrix3D vView = mat4:(vec3(0.0f, 0.0f, 20.0f));

	// for every game object
	for (auto& obj : GOM->GameObjList())
	{
		// draw the active game objects that has active mesh components
		if (obj.IsActive() && obj.GetComponent<Mesh>() && obj.GetComponent<Mesh>()->IsActive())
			DrawObject(obj, _viewMatrix, vProj);
	}

	// swap buffers
	_pWindow->display();
}

void Graphics::Unload()
{
	for (auto it = _textures.begin(); it != _textures.end(); ++it)
		delete it->second;
	cout << "Graphics System unloaded." << endl;
}

void Graphics::Cleanup()
{
	if (_pWindow)	delete _pWindow;
	cout << "Graphics System cleaned up.\n";
}

void Graphics::UpdateWindowSize(unsigned int w, unsigned int h)
{
	_width = w;
	_heigth = h;
}

void Graphics::RenderPauseMenu()
{
	Matrix3D proj, view;
	GameObject* obj = GOM->GetMenu();

	if (!obj) return;
	GFX->DrawObject(*obj, view, proj);
	_pWindow->display();
}
