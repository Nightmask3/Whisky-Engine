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
	// Trying out stuff
	sf::Time newTime_, currentTime_, frameTime_;
	double ft_;
	
	static FrameRateController* Inst();

	bool Init(unsigned);
	void Begin();
	void End();

	void ToggleFPSLock();

	inline double FrameDelta() { return frameDelta_; }
	inline unsigned FPS()			const	{ return fps_; }
	void Update();
	inline double	 Time()			const   { return time_.getElapsedTime().asSeconds(); }
	inline double FrameTimeLimit() const { return frameTimeLimit_; }
	inline double GetTotalTime() { return totalTime_; }
	inline void AddtoTotalTime(double time) { totalTime_ += time; }
	inline unsigned long FrameCount() const { return frameCount_; }
private:
	FrameRateController(){}
	~FrameRateController(){}

	static FrameRateController* _pInstance;

	unsigned fps_;
	double frameTimeLimit_;	// seconds
	double frameDelta_;		// seconds
	double begin_, end_;
	double totalTime_;
	unsigned long frameCount_;
	sf::Clock time_;

};

#endif