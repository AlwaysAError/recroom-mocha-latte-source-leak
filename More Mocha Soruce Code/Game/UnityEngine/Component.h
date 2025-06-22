#pragma once

struct GameObject;
struct Transform;

struct Component : UObject {
	typedef GameObject* (*get_gameObject_t)(Component* component);
	GameObject* get_gameObject() {
		const auto func = (get_gameObject_t)(methods::UnityEngine::Component::get_gameObject);
		return func(this);
	}

	typedef Transform* (*get_transform_t)(Component* component);
	Transform* get_transform() {
		const auto func = (get_transform_t)(methods::UnityEngine::Component::get_transform);
		return func(this);
	}

};