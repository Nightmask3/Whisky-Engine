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
	fps_ = fps;
	frameTimeLimit_ = 1.0f / fps_;
	frameCount_ = 0;
	frameDelta_ = begin_ = end_ = 0.0f;
	totalTime_ = 0;
	// Starts the clock
	time_ = sf::Clock();
	currentTime_ = newTime_ = frameTime_ = sf::Time();
	cout << "FrameRateController Initialized: " << fps_ << " FPS | FrameTimeLimit = " << frameTimeLimit_ << endl;

	return true;
}

void FrameRateController::Begin()
{
	begin_ = Time();
}

void FrameRateController::End()
{
	while ((frameDelta_ = (Time() - begin_)) < frameTimeLimit_);	// FPS lock
	++frameCount_;
}

void FrameRateController::ToggleFPSLock()
{
	if (fps_ == 60){
		fps_ = 150;
	}
	else
	{
		fps_ = 60;
	}

	frameTimeLimit_ = 1.0f / fps_;

}

void FrameRateController::Update()
{
	newTime_ = time_.getElapsedTime();
	frameTime_ = newTime_ - currentTime_;
	ft_ = frameTime_.asSeconds();
	currentTime_ = newTime_;
	// For independent timestep
	//totalTime_ += ft_;
}