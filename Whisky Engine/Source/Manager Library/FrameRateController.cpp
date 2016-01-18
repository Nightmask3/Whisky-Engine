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

#include "FrameRateController.h"
#include <iostream>

using std::cout;
using std::endl;

#include "..\..\Engine.h"

FrameRateController* FrameRateController::_pInstance = NULL;

FrameRateController* FrameRateController::Inst()
{
		if (_pInstance == NULL) _pInstance = new FrameRateController();

		return _pInstance;
}

bool FrameRateController::Init(unsigned fps)
{
	_fps = fps;
	_frameTimeLimit = 1.0f / _fps;
	_frameCount = 0;
	_frameDelta = _begin = _end = 0.0f;
	cout << "FrameRateController Initialized: " << _fps << " FPS | FrameTimeLimit = " << _frameTimeLimit << endl;
	return true;
}

void FrameRateController::Begin()
{
	_begin = Time();
}

void FrameRateController::End()
{
	while ((_frameDelta = (Time() - _begin)) < _frameTimeLimit);	// FPS lock
	++_frameCount;
}

void FrameRateController::ToggleFPSLock()
{
	if (_fps == 60){
		_fps = 150;
	}
	else
	{
		_fps = 60;
	}

	_frameTimeLimit = 1.0f / _fps;

}