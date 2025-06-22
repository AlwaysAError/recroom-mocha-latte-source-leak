#pragma once

struct RecRoomSceneManager : MonoBehaviourPun {

	typedef RecRoomSceneManager* (*get_Instance_t)();
	static RecRoomSceneManager* get_Instance() {
		const auto func = (get_Instance_t)(methods::RecRoomSceneManager::get_Instance);
		return func();
	}

};