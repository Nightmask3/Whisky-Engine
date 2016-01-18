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

#ifndef FRAMERATECONTROLLER_H
#define FRAMERATECONTROLLER_H

#include<sfml/System.hpp>

class FrameRateController
{
public:
	static FrameRateController* Inst();

	bool Init(unsigned);
	void Begin();
	void End();

	void ToggleFPSLock();

	float	 FrameDelta()	const	{ return _frameDelta; }
	unsigned FPS()			const	{ return _fps; }
	float	 Time()			const   { return _time.getElapsedTime().asSeconds(); }
	float FrameTimeLimit() const { return _frameTimeLimit; }
	unsigned long FrameCount() const { return _frameCount; }
private:
	FrameRateController(){}
	~FrameRateController(){}

	static FrameRateController* _pInstance;

	unsigned _fps;
	float _frameTimeLimit;	// seconds
	float _frameDelta;
	float _begin, _end;
	unsigned long _frameCount;
	sf::Clock _time;

};

#endif