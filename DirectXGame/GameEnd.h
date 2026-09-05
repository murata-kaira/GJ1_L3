#pragma once

#include "Fade.h"
#include "KamataEngine.h"

class GameEnd {
public:
	enum class Phase {
		kFadeIn,
		kMain,
		kFadeOut,
	};

	~GameEnd();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelPlayer_ = nullptr;

	KamataEngine::Camera camera_;

	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::WorldTransform worldTransformPlayer_;

	float rotate = 0.0f;

	bool finished_ = false;

	Fade* fade_ = nullptr;

	Phase phase_ = Phase::kFadeIn;
};
