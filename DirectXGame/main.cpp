#include "GameScene.h"
#include "GameOverScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include <Windows.h>

using namespace KamataEngine;

GameScene* gameScene = nullptr;
GameOverScene* gameOverScene = nullptr;
TitleScene* titleScene = nullptr;


enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
	kGameOver,

};

Scene scene = Scene::kUnknown;

void ChangeScene() {
	switch (scene) { case Scene::kTitle:
		if (titleScene->IsFinished()) {
		
			scene = Scene::kGame;

			delete titleScene;
			titleScene = nullptr;

			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsFnished()) {
		
			delete gameScene;
			gameScene = nullptr;

			scene = Scene::kGameOver;
			gameOverScene = new GameOverScene;
			gameOverScene->Initialize();
		}
		break;
	case Scene::kGameOver:
		if (gameOverScene->IsFinished()) {
			bool shouldRetry = gameOverScene->ShouldRetry();
			delete gameOverScene;
			gameOverScene = nullptr;

			if (shouldRetry) {
				scene = Scene::kGame;
				gameScene = new GameScene;
				gameScene->Initialize();
			} else {
				scene = Scene::kTitle;
				titleScene = new TitleScene;
				titleScene->Initialize();
			}
		}
		break;
	}

}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();
		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	case Scene::kGameOver:
		gameOverScene->Update();
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kGameOver:
		gameOverScene->Draw();
		break;
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	KamataEngine::Initialize(L"LE2D_23_ムラタ_カイラ_AL3");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	scene = Scene::kTitle;
	titleScene =  new TitleScene;
	titleScene->Initialize();


	while (true) {

		if (KamataEngine::Update()) {
			break;
		}

		ChangeScene();

		UpdateScene();

		dxCommon->PreDraw();

		DrawScene();

		dxCommon->PostDraw();
	}

	delete gameScene;
	delete gameOverScene;
	delete titleScene;

	KamataEngine::Finalize();

	return 0;
}
