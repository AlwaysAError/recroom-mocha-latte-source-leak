#pragma once

struct Camera : Behaviour {

	typedef Camera* (*get_current_t)();
	static Camera* get_current() { // using get_main always returns a nullptr :-)
		const auto func = (get_current_t)(methods::UnityEngine::Camera::get_current);
		return func();
	}

	typedef Vector2(*WorldToScreenPoint_t)(Camera* camera, Vector3 position);
	Vector2 WorldToScreenPoint(Vector3 position) { // none of the WorldToScreenPoint functions in the Camera class work without issues
		const auto func = (WorldToScreenPoint_t)(methods::UnityEngine::RectTransformUtility::WorldToScreenPoint);
		return func(this, position);
	}

	typedef float(*get_fieldOfView_t)(Camera* camera);
	float get_fieldOfView() {
		const auto func = (get_fieldOfView_t)(methods::UnityEngine::Camera::get_fieldOfView);
		return func(this);
	}

};