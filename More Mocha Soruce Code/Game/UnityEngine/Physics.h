#pragma once

struct Physics : UObject {

	typedef void (*set_gravity_t)(Vector3 value);
	static void set_gravity(Vector3 value) {
		const auto func = (set_gravity_t)(methods::UnityEngine::Physics::set_gravity);
		return func(value);
	}

	typedef Vector3(*get_gravity_t)();
	static Vector3 get_gravity() {
		const auto func = (get_gravity_t)(methods::UnityEngine::Physics::get_gravity);
		return func();
	}

};