#pragma once

#include "Fade.h"
#include "KamataEngine.h"

class GameOverScene {
public:
	~GameOverScene();

	void Initialize();
	void Update();
	void Draw();

	bool IsFinished() const { return finished_; }
	bool ShouldRetry() const { return shouldRetry_; }

private:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	KamataEngine::Sprite* background_ = nullptr;
	Fade* fade_ = nullptr;
	Phase phase_ = Phase::kFadeIn;
	bool finished_ = false;
	bool shouldRetry_ = false;
};
