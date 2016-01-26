// ---------------------------------------------------------------------------
// Project Name		:	Whisky Engine
// File Name		:	Engine.cpp
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

#include "Engine.h"

#include <iomanip>
#include <cassert>

#include "Source\Component Library\CameraComponent.h"  //remove when camera init code is moved!!!!!!

using std::cout;
using std::endl;


bool Engine::_quit = false;
bool Engine::_debugDraw = false;
bool Engine::_collisionInfo = false;
bool Engine::_info = false;
bool Engine::_pause = false;


const float Engine::version_ = 0.7f;
unsigned Engine::_resolution_w = 1280;
unsigned Engine::_resolution_h = 720;

void Engine::ToggleInfo()
{

	if (_info)		std::cout << "\nInfo Logging Stopped.\n";
	_info = !_info;
}

void Engine::TogglePause()
{
	_pause = !_pause;

	if (_pause) GFX->RenderPauseMenu();
	else	   GOM->GetMenu()->GetComponent<Mesh>()->SetActive(false);
}

void print(std::string s)
{
	cout << "-----------------------------------------" << endl;
	cout << "|\t Whisky Engine " << s << " \t|" << endl;
	cout << "-----------------------------------------" << endl;
}

bool Engine::Init()
{
	print("Initializing...");
	srand((unsigned)time(NULL));

	// initialize systems
	if (!FRC->Init(60) ||	// frame rate controller
		//!PHY->Init() ||	// physics
		!RSC->Init() ||		// resource manager
		!GFX->Init() ||		// graphics
		!INP->Init() ||		// input controller
		!GOM->Init() //||		// game object manager
		//!MSG->Init()		// messaging 
		)
		return false;

	print("Initialized ");
	return true;
}

bool Engine::Load()
{
	print("Loading... \t");


	if (!RSC->Load("Level.txt") ||
		!GFX->Load() ||
		!GOM->Load()
		)
		return false;

	print("Loaded \t");


	///////////////////////////////////////////////////////////////////////////////
	//// Game Object Creation Example

	GameObject & obj = GOM->Instantiate();	
	obj.GetComponent<Transform>()->Scale(0.5f, 0.5f, 0.5f);
	obj.GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, 10.0f));
	CameraComponent* cam = new CameraComponent();
	obj.AddComponent(cam);
	PlayerController* ctrl = new PlayerController();	//temporary camera behavior controller until dampening is added
	obj.AddComponent(ctrl);
	GOM->SetCamera(&obj);

	/*GameObject & obj2 = GOM->Instantiate();
	obj2.GetComponent<Transform>()->Scale(0.5f, 0.5f, 0.5f);
	obj2.GetComponent<Transform>()->Translate(glm::vec3(0.0f, 0.0f, 0.0f));
	//PlayerController* ctrl2 = new PlayerController();
	//obj2.AddComponent(ctrl2);
	Mesh* msh = new Mesh(QUAD);
	obj2.AddComponent(msh);
	GOM->SetPlayer(&obj2);*/

	///CAMERA NOT DELETED SO MEMORY LEAK HERE ALTHOUGH VERY SMALL


	GameObject & obj3 = GOM->Instantiate();				// instantiated with a default transform component
	obj3.GetComponent<Transform>()->Scale(0.1f, 5.0f, 5.0f);
	obj3.GetComponent<Transform>()->Translate(glm::vec3(4.0f, 0.0f, 0.0f));
	// Add component to component list of object, then add handle to handle list
	Mesh * mesh = new Mesh(MeshType::CUBE, Color::black);	// new component to be added
	obj3.AddComponent(mesh);

	Audio* audio = new Audio();
	SimpleMusic* music = new SimpleMusic("greatmusic.ogg");
	SimpleAudioSource* audioSource = new SimpleAudioSource("scream.wav");
	SimpleSFX* sfx = new SimpleSFX("scream.wav");
	AM->registerSFX(audio, sfx);
	obj.AddComponent(audio);
	//PlayerController* ctrl = new PlayerController();
	//obj.AddComponent(ctrl);

	return true;
}

void Engine::MainLoop()
{
	if (_pause)  GFX->RenderPauseMenu();
	while (!_quit)
	{
		FRC->Begin();		// start frame

		// read user inputS
		INP->Update();		// input manager

		if (!_pause)
		{
			// update world
			GOM->Update();		// game object manager
			//PHY->Update();	// physics

			// render
			GFX->Render();		// graphics(mode)

		}

		FRC->End();			// end frame
		if (_info)	Log();
	}
}

void Engine::Unload()
{
	cout << endl;
	print("Unloading...");

	GFX->Unload();

	print("Unloaded \t");
}

void Engine::Exit()
{
	print("Cleaning Up... ");

	// cleanup systems
	//INP->Cleanup();
	GFX->Cleanup();

	// print info
	cout << "VolkEngine exiting..." << endl;
}

void Engine::Log() const
{
	// CAUTION: Printing to console may increase frame time (noticeable at switching to higher fps)
	cout << std::setprecision(4)
		<< "FrameDelta: " << FRC->FrameDelta() * 1000 << "ms | " << FRC->FrameTimeLimit() * 1000 << "ms"
		<< "  FPS: " << (int)(1.0f / FRC->FrameDelta()) + 1
		<< "  Frame: #" << FRC->FrameCount()
		<< "  DebugDraw: " << _debugDraw
		<< "  CollisionLog: " << _collisionInfo
		<< "  GameObjects: " << GOM->GetActiveObjCount() << "/" << GOM->GameObjList().size()
		<< " \r";
	fflush(stdout);
}
