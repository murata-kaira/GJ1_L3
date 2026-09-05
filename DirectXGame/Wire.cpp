#include "Wire.h"
#include <cmath>

void Wire::Initialize() {
	isActive_ = false;
	isConnected_ = false;
	startPosition_ = {};
	endPosition_ = {};
	hookPosition_ = {};
}

void Wire::Update(const Vector3& playerPosition, const Vector3& playerDirection) {
	if (!isActive_) {
		return;
	}

	if (isConnected_) {
		startPosition_ = playerPosition;
		return;
	}

	endPosition_.x += playerDirection.x * wireSpeed_;
	endPosition_.y += playerDirection.y * wireSpeed_;
	endPosition_.z += playerDirection.z * wireSpeed_;

	startPosition_ = playerPosition;

	Vector3 distance = endPosition_;
	distance.x -= startPosition_.x;
	distance.y -= startPosition_.y;
	distance.z -= startPosition_.z;

	float length = std::sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);

	if (length >= maxDistance_) {
		Release();
	}
}

void Wire::Shoot(const Vector3& playerPosition, const Vector3& direction) {
	isActive_ = true;
	isConnected_ = false;

	startPosition_ = playerPosition;
	endPosition_ = playerPosition;

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

	Vector3 normalizedDirection = direction;

	if (length > 0.0f) {
		normalizedDirection.x /= length;
		normalizedDirection.y /= length;
		normalizedDirection.z /= length;
	}

	endPosition_.x += normalizedDirection.x * wireSpeed_;
	endPosition_.y += normalizedDirection.y * wireSpeed_;
	endPosition_.z += normalizedDirection.z * wireSpeed_;
}

void Wire::Release() {
	isActive_ = false;
	isConnected_ = false;
}

void Wire::Connect(const Vector3& position) {
	isConnected_ = true;
	hookPosition_ = position;
	endPosition_ = position;
}

bool Wire::IsConnected() const { return isConnected_; }

bool Wire::IsActive() const { return isActive_; }

const Vector3& Wire::GetStartPosition() const { return startPosition_; }

const Vector3& Wire::GetEndPosition() const { return endPosition_; }

const Vector3& Wire::GetHookPosition() const { return hookPosition_; }