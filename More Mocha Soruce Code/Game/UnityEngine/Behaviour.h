#pragma once

struct Behaviour : Component {
	typedef bool (*get_enabled_t)(Behaviour* behaviour);
	bool get_enabled() {
		const auto func = (get_enabled_t)(methods::UnityEngine::Behaviour::get_enabled);
		return func(this);
	}

	typedef void (*set_enabled_t)(Behaviour* behaviour, bool enabled);
	void set_enabled(bool enabled) {
		const auto func = (set_enabled_t)(methods::UnityEngine::Behaviour::set_enabled);
		return func(this, enabled);
	}

	typedef bool (*get_isActiveAndEnabled_t)(Behaviour* behaviour);
	bool get_isActiveAndEnabled() {
		const auto func = (get_isActiveAndEnabled_t)(methods::UnityEngine::Behaviour::get_isActiveAndEnabled);
		return func(this);
	}

};