#pragma once

struct CircuitsV2Manager : MonoBehaviourPun {

	typedef CircuitsV2Manager* (*GetCircuitsV2Manager_t)();
	static CircuitsV2Manager* GetCircuitsV2Manager() {
		const auto func = (GetCircuitsV2Manager_t)(GameAssembly + 0x12D13C0); // search term -> "static RecRoom::CircuitsV2::CircuitsV2Manager* "
		return func();
	}

	typedef void (*RpcSendMajorNotification_t)(CircuitsV2Manager* instance, Il2CppString* message);
	void RpcSendMajorNotification(Il2CppString* message) {
		const auto func = (RpcSendMajorNotification_t)(methods::CircuitsV2::CircuitsV2Manager::RpcSendMajorNotification);
		return func(this, message);
	}

};