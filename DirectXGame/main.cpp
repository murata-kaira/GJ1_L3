#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include "GameEnd.h"
#include "GameOver.h"
#include <Windows.h>

using namespace KamataEngine;

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;
GameEnd* gameEnd = nullptr;
GameOver* gameOver = nullptr;

enum class Scene {
	kUnknown = 0,
	kTitle,
	kGame,
	kEnd,
	kOver,
};

Scene scene = Scene::kUnknown;

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
		
			scene = Scene::kGame;

			delete titleScene;
			titleScene = nullptr;

			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsPauseReturn()) {
		
			scene = Scene::kTitle;

			delete gameScene;
			gameScene = nullptr;

				titleScene = new TitleScene;
			titleScene->Initialize();
		} else if (gameScene->IsFnished()) {
			scene = Scene::kOver;
			delete gameScene;
			gameScene = nullptr;
			gameOver = new GameOver;
			gameOver->Initialize();
		} else if (gameScene->IsClear()) {
			scene = Scene::kEnd;
			delete gameScene;
			gameScene = nullptr;
			gameEnd = new GameEnd;
			gameEnd->Initialize();
		}
		break;
	case Scene::kEnd:
		if (gameEnd->IsFinished()) {
			scene = Scene::kTitle;
			delete gameEnd;
			gameEnd = nullptr;

			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	case Scene::kOver:
		if (gameOver->IsFinished()) {
			scene = Scene::kTitle;
			delete gameOver;
			gameOver = nullptr;

			titleScene = new TitleScene;
			titleScene->Initialize();
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
	case Scene::kEnd:
		gameEnd->Update();
		break;
	case Scene::kOver:
		gameOver->Update();
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
	case Scene::kEnd:
		gameEnd->Draw();
		break;
	case Scene::kOver:
		gameOver->Draw();
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
	delete titleScene;
	delete gameEnd;
	delete gameOver;

	KamataEngine::Finalize();

	return 0;
}
