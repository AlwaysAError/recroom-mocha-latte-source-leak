#pragma once

struct Time : Il2CppObject {

	typedef float (*get_Time_t)();
	static float get_Time() {
		const auto func = (get_Time_t)(methods::UnityEngine::Time::get_Time);
		return func();
	}

	typedef float (*get_deltaTime_t)();
	static float get_deltaTime() {
		const auto func = (get_deltaTime_t)(methods::UnityEngine::Time::get_deltaTime);
		return func();
	}

};