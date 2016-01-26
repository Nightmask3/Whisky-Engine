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
	void Update();

	sf::Time newTime, frameTime, currentTime;
	double frametime;
	void ToggleFPSLock();

	inline float FrameDelta() { return frameDelta_; }
	inline unsigned FPS()			const	{ return fps_; }
	inline float	 Time()			const   { return time_.getElapsedTime().asSeconds(); }
	inline float FrameTimeLimit() const { return frameTimeLimit_; }
	inline double GetTotalTime() { return totalTime_; }
	inline void AddtoTotalTime(double time) { totalTime_ += time; }
	inline unsigned long FrameCount() const { return frameCount_; }
private:
	FrameRateController(){}
	~FrameRateController(){}

	static FrameRateController* _pInstance;

	unsigned fps_;
	float frameTimeLimit_;	// seconds
	float begin_, end_;
	double totalTime_;
	unsigned long frameCount_;
	sf::Clock time_;

	float frameDelta_;

};

#endif