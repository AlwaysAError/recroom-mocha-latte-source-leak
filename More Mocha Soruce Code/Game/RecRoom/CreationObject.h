#pragma once

struct CreationObject : MonoBehaviourPun {

	typedef bool (*Scale_t)(CreationObject* CreationObject, float scale);
	bool Scale(float scale) {
		const auto func = (Scale_t)(methods::CreationObject::Scale);
		return func(this, scale);
	}

	typedef bool (*get_IsFrozen_t)(CreationObject* CreationObject);
	bool get_IsFrozen() {
		const auto func = (get_IsFrozen_t)(methods::CreationObject::get_IsFrozen);
		return func(this);
	}

	typedef bool (*set_IsFrozen_t)(CreationObject* CreationObject, bool enabled);
	bool set_IsFrozen(bool enabled) {
		const auto func = (set_IsFrozen_t)(methods::CreationObject::set_IsFrozen);
		return func(this, enabled);
	}

	typedef bool (*get_IsGrabbable_t)(CreationObject* CreationObject);
	bool get_IsGrabbable() {
		const auto func = (get_IsGrabbable_t)(methods::CreationObject::get_IsGrabbable);
		return func(this);
	}

	typedef bool (*set_IsGrabbable_t)(CreationObject* CreationObject, bool enabled);
	bool set_IsGrabbable(bool enabled) {
		const auto func = (set_IsGrabbable_t)(methods::CreationObject::set_IsGrabbable);
		return func(this, enabled);
	}

	typedef bool (*get_Initialized_t)(CreationObject* CreationObject);
	bool get_Initialized() {
		const auto func = (get_Initialized_t)(methods::CreationObject::get_Initialized);
		return func(this);
	}

	typedef bool (*set_DynamicCollisionEnabled_t)(CreationObject* CreationObject, bool enabled);
	bool set_DynamicCollisionEnabled(bool enabled) {
		const auto func = (set_DynamicCollisionEnabled_t)(methods::CreationObject::set_DynamicCollisionEnabled);
		return func(this, enabled);
	}

};