#pragma once

#include "KamataEngine.h"

using namespace KamataEngine;

class Wire {
public:
	// 初期化
	void Initialize();

	// 更新
	void Update(const Vector3& playerPosition, const Vector3& playerDirection);

	// ワイヤーを発射
	void Shoot(const Vector3& playerPosition, const Vector3& direction);

	// ワイヤーを解除
	void Release();

	// 接続
	void Connect(const Vector3& position);

	// 接続中か
	bool IsConnected() const;

	// 発射中か
	bool IsActive() const;

	// ワイヤーの始点
	const Vector3& GetStartPosition() const;

	// ワイヤーの先端
	const Vector3& GetEndPosition() const;

	// フック地点
	const Vector3& GetHookPosition() const;

private:
	// ワイヤーが有効か
	bool isActive_ = false;

	// ブロックに接続しているか
	bool isConnected_ = false;

	// ワイヤーの始点
	Vector3 startPosition_{};

	// ワイヤーの先端
	Vector3 endPosition_{};

	// ブロックに接続した位置
	Vector3 hookPosition_{};

	// ワイヤーの速度
	float wireSpeed_ = 1.0f;

	// 最大射程
	float maxDistance_ = 30.0f;
};