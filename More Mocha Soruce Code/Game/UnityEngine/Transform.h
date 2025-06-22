#pragma once

struct Transform : Component {

	typedef Vector3(*get_position_t)(Transform* transform);
	Vector3 get_position() {
		const auto func = (get_position_t)(methods::UnityEngine::Transform::get_position);
		return func(this);
	}

	typedef void(*set_localPosition_t)(Transform* transform, Vector3 pos);
	void set_localPosition(Vector3 position) {
		const auto func = (set_localPosition_t)(methods::UnityEngine::Transform::set_localPosition);
		return func(this, position);
	}

	typedef int32_t(*get_ChildCount_t)(Transform* transform);
	int32_t get_ChildCount() {
		const auto func = (get_ChildCount_t)(methods::UnityEngine::Transform::get_childCount);
		return func(this);
	}

	typedef Transform* (*getChild_t)(Transform* transform, int32_t childCount);
	Transform* GetChild(int32_t childCount) {
		const auto func = (getChild_t)(methods::UnityEngine::Transform::GetChild);
		return func(this, childCount);
	}

	typedef Vector3(*get_localScale_t)(Transform* transform);
	Vector3 get_localScale() {
		const auto func = (get_localScale_t)(methods::UnityEngine::Transform::get_localScale);
		return func(this);
	}

	typedef void(*set_localScale_t)(Transform* transform, Vector3 scale);
	void set_localScale(Vector3 scale) {
		const auto func = (set_localScale_t)(methods::UnityEngine::Transform::set_localScale);
		return func(this, scale);
	}

	typedef void(*setParent_t)(Transform* transform, Transform* parent);
	void SetParent(Transform* parent) {
		const auto func = (setParent_t)(methods::UnityEngine::Transform::SetParent);
		return func(this, parent);
	}

	typedef Transform* (*getParent_t)(Transform* transform);
	Transform* get_parent() {
		const auto func = (getParent_t)(methods::UnityEngine::Transform::get_parent);
		return func(this);
	}

	typedef Transform* (*findTransform_t)(Transform* transform, Il2CppString* name);
	Transform* Find(Il2CppString* name) {
		const auto func = (findTransform_t)(methods::UnityEngine::Transform::Find);
		return func(this, name);
	}

	typedef Quaternion(*get_localRotation_t)(Transform* transform);
	Quaternion get_localRotation() {
		const auto func = (get_localRotation_t)(methods::UnityEngine::Transform::get_localRotation);
		return func(this);
	}

	typedef void (*set_localRotation_t)(Transform* transform, Quaternion rot);
	void set_localRotation(Quaternion rotation) {
		const auto func = (set_localRotation_t)(methods::UnityEngine::Transform::set_localRotation);
		return func(this, rotation);
	}

	typedef Vector3(*get_forward_t)(Transform* transform);
	Vector3 get_forward() {
		const auto func = (get_forward_t)(methods::UnityEngine::Transform::get_forward);
		return func(this);
	}

	typedef Vector3(*get_up_t)(Transform* transform);
	Vector3 get_up() {
		const auto func = (get_up_t)(methods::UnityEngine::Transform::get_up);
		return func(this);
	}

	typedef Vector3(*get_right_t)(Transform* transform);
	Vector3 get_right() {
		const auto func = (get_right_t)(methods::UnityEngine::Transform::get_right);
		return func(this);
	}

	typedef void(*set_position_t)(Transform* transform, Vector3 pos);
	void set_position(Vector3 position) {
		const auto func = (set_position_t)(methods::UnityEngine::Transform::set_position);
		return func(this, position);
	}

	typedef Quaternion(*get_rotation_t)(Transform* transform);
	Quaternion get_rotation() {
		const auto func = (get_rotation_t)(methods::UnityEngine::Transform::get_rotation);
		return func(this);
	}

	typedef void(*set_rotation_t)(Transform* transform, Quaternion rotation);
	void set_rotation(Quaternion position) {
		const auto func = (set_rotation_t)(methods::UnityEngine::Transform::set_rotation);
		return func(this, position);
	}
};