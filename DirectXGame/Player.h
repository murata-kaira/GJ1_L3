#pragma once
#include "KamataEngine.h"
#include "MyMath.h"
#include"Enemy.h"

class MapChipField;
class Enemy;
class Player {

public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	void Draw();

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	AABB GetAABB();

	void OnCollision(const Enemy* enemy);

	 KamataEngine::Vector3 GetWorldPosition();


	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }
	bool HasWire() const { return hasWire_; }
	const KamataEngine::Vector3& GetWireAnchor() const { return wireAnchor_; }

	bool IsDead() const { return isDead_; }


private:
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	MapChipField* mapChipField_ = nullptr;

	KamataEngine::Vector3 velocity_ = {};

	
	

	static inline const float kAcceleration = 0.5f;

	static inline const float kAttenuation = 0.5;

	static inline const float kLimitRunSpeed = 0.25f;

	// ワイヤー接続中に毎フレーム加える横方向の加速度。
	static inline const float kWireAttachAcceleration = 0.02f;

	// ワイヤーで振れている間だけ使用する最大横速度。
	static inline const float kLimitWireSpeed = 0.5f;

	static inline const float kTimeTurn = 0.3f;

	static inline const float kGravityAcceleration = 0.05f;

	static inline const float kLimitFallSpeed = 0.5f;

	static inline const float kJumpAcceleration = 1.0f;

	static inline const float kWidth = 0.8f;

	static inline const float kHeight = 0.8f;

	bool onGround_ = true;
	bool hasWire_ = false;
	// ワイヤーが壁に刺さった座標と、接続時に決まるワイヤーの長さ。
	KamataEngine::Vector3 wireAnchor_ = {};
	float wireLength_ = 0.0f;
	// 接続時に保存する、ワイヤーを発射した左右方向（右: 1、左: -1）。
	float wireAttachDirectionX_ = 0.0f;

	enum class LRDirection {
		kRight,
		kLeft,
	};

	LRDirection lrDirection_ = LRDirection::kRight;

	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;

	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		KamataEngine::Vector3 move;
	};

	bool isDead_ = false;

	void InputMove();
	void UpdateWire();
	bool TryAttachWire();

	void CheckMapCollision(CollisionMapInfo& info);

	void CheckMapCollisionUp(CollisionMapInfo& info);

	void CheckMapCollisionDown(CollisionMapInfo& info);

	void CheckMapCollisionRight(CollisionMapInfo& info);

	void CheckMapCollisionLeft(CollisionMapInfo& info);



	void CheckMapMove(const CollisionMapInfo& info);

	void CheckMapCeiling(const CollisionMapInfo& info);

	void CheckMapWall(const CollisionMapInfo& info);


	void CheckMapLanding(const CollisionMapInfo& info);


	void AnimateTurn();

	enum Corner {
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner
	};

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

	static inline const float kBlank = 0.1f;

	static inline const float kAttenuationLanding = 0.5f;

	static inline const float kGroundSearchHeight = 0.1f;

	static inline const float kAttenuationWall = 0.5f;
};
