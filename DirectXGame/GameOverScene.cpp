#include "GameOverScene.h"

using namespace KamataEngine;

GameOverScene::~GameOverScene() {
	delete background_;
	delete fade_;
}

void GameOverScene::Initialize() {
	uint32_t textureHandle = TextureManager::Load("white1x1.png");
	background_ = Sprite::Create(textureHandle, {0.0f, 0.0f}, {0.25f, 0.0f, 0.0f, 0.85f});
	background_->SetSize({1280.0f, 720.0f});

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 0.5f);
}

void GameOverScene::Update() {
	switch (phase_) {
	case Phase::kFadeIn:
		fade_->Update();
		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kMain:
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			shouldRetry_ = true;
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 0.5f);
		} else if (Input::GetInstance()->TriggerKey(DIK_ESCAPE)) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 0.5f);
		}
		break;
	case Phase::kFadeOut:
		fade_->Update();
		if (fade_->IsFinished()) {
			finished_ = true;
		}
		break;
	}
}

void GameOverScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(dxCommon->GetCommandList());
	background_->Draw();
	Sprite::PostDraw();

	DebugText* debugText = DebugText::GetInstance();
	debugText->Print("GAME OVER", 480.0f, 280.0f, 3.0f);
	debugText->Print("SPACE : RETRY", 500.0f, 390.0f, 1.5f);
	debugText->Print("ESC : TITLE", 520.0f, 430.0f, 1.5f);
	debugText->DrawAll();

	fade_->Draw();
}
