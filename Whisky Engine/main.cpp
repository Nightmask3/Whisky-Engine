
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

#include "Engine.h"

using std::cout;
using std::endl;

int main()
{

	Engine WhiskyEngine;
	if (!WhiskyEngine.Init())	return -1;
	if (!WhiskyEngine.Load()) return -2;
	WhiskyEngine.MainLoop();
	WhiskyEngine.Unload();
	WhiskyEngine.Exit();

	//std::cout << "r1= " << &r1 << "\tr2= " << &r2 << std::endl
	//	<< "p1= " << p1 << "\tp2= " << p2 << std::endl;

	return 0;
}