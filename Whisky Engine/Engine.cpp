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
		!RSC->Init() ||		// resource manager
		!GFX->Init() ||		// graphics
		!INP->Init() ||		// input controller
		!GOM->Init() ||		// game object manager
		!PHY->Init()		// physics
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

	// Cube 1
	GameObject & cube1 = GOM->Instantiate();				// instantiated with a default transform component
	cube1.GetComponent<Transform>()->Scale(2.0f, 2.0f, 2.0f);
	cube1.GetComponent<Transform>()->Translate(glm::vec3(8.0f, 10.0f, 0.0f));

	Transform * trans1 = cube1.GetComponent<Transform>();
	Mesh * mesh = new Mesh(MeshType::CUBE, Color::black);
	cube1.AddComponent(mesh);

	PhysicsComponent * phy = new PhysicsComponent();
	cube1.AddComponent(phy);
	phy->SetCurrentPosition(trans1->GetPosition());
	phy->SetBoundingBoxType(Bounding::RigidBodyType::AABB);

	PHY->AddComponentToList(phy);
	// Cube 2
	GameObject & cube2 = GOM->Instantiate();				
	cube2.GetComponent<Transform>()->Scale(1.0f, 1.0f, 1.0f);
	cube2.GetComponent<Transform>()->Translate(glm::vec3(-8.0f, 5.0f, 0.0f));

	Transform * trans2 = cube2.GetComponent<Transform>();
	Mesh * mesh2 = new Mesh(MeshType::CUBE, Color::black);	
	cube2.AddComponent(mesh2);

	PhysicsComponent * phy2 = new PhysicsComponent();
	cube2.AddComponent(phy2);
	phy2->SetCurrentPosition(trans2->GetPosition());
	phy2->SetBoundingBoxType(Bounding::RigidBodyType::AABB);
	PHY->AddComponentToList(phy2);

	// Cube 3
	GameObject & cube3 = GOM->Instantiate();				
	cube3.GetComponent<Transform>()->Scale(2.5f, 2.5f, 2.5f);
	cube3.GetComponent<Transform>()->Translate(glm::vec3(0.0f, 5.0f, 0.0f));


	Transform * trans3 = cube3.GetComponent<Transform>();
	Mesh * mesh3 = new Mesh(MeshType::CUBE, Color::black);
	cube3.AddComponent(mesh3);

	PhysicsComponent * phy3 = new PhysicsComponent();
	cube3.AddComponent(phy3);
	phy3->SetCurrentPosition(trans3->GetPosition());
	phy3->SetBoundingBoxType(Bounding::RigidBodyType::AABB);

	PHY->AddComponentToList(phy3);

	// Plane creation
	GameObject & plane = GOM->Instantiate();
	
	Transform * trans4 = plane.GetComponent<Transform>();
	trans4->Scale(20.5f, 2.5f, 20.5f);
	trans4->Translate(glm::vec3(0.0f, -10.0f, 0.0f));

	Mesh * mesh4 = new Mesh(MeshType::CUBE, Color::black);
	plane.AddComponent(mesh4);

	PhysicsComponent * phy4 = new PhysicsComponent();
	plane.AddComponent(phy4);
	phy4->SetCurrentPosition(trans4->GetPosition());
	phy4->SetBoundingBoxType(Bounding::RigidBodyType::PLANE);
	phy4->SetMass(0);
	PHY->AddComponentToList(phy4);

	// Sound creation
	Audio* audio = new Audio();
	SimpleMusic* music = new SimpleMusic("greatmusic.ogg");
	SimpleAudioSource* audioSource = new SimpleAudioSource("scream.wav");
	SimpleSFX* sfx = new SimpleSFX("scream.wav");
	AM->registerSFX(audio, sfx);
	cube1.AddComponent(audio);


	return true;
}

void Engine::MainLoop()
{
	if (_pause)  GFX->RenderPauseMenu();
	while (!_quit)
	{
		FRC->Begin();		// start frame
		//FRC->Update();
		// read user inputS
		INP->Update();		// input manager

		if (!_pause)
		{
			// update world
			GOM->Update();		// game object manager
			PHY->Update();	// physics

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
